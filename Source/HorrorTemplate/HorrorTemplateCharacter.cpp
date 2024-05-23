// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorTemplateCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TeaseSystem.h"
#include "Components/TimelineComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Public/InteractComponent.h"
#include "Public/PlayerDataAsset.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AHorrorTemplateCharacter

AHorrorTemplateCharacter::AHorrorTemplateCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 96.0f);
		
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 0;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f)); // Position the camera
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 25.f;
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f)); 
	FirstPersonCameraComponent->bUsePawnControlRotation = false;

	CameraCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CameraCollision"));
	CameraCollision->SetupAttachment(FirstPersonCameraComponent);
	CameraCollision->InitSphereRadius(22.5f);
	CameraCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CameraCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CameraCollision->SetGenerateOverlapEvents(true);
	CameraCollision->OnComponentBeginOverlap.AddDynamic(this, &AHorrorTemplateCharacter::OnComponentOverlap);

	LeanLeft = CreateDefaultSubobject<USceneComponent>(TEXT("LeanLeft"));
	LeanLeft->SetupAttachment(RootComponent);
	LeanLeft->SetWorldLocation(FVector(0.f, -40.f, 60.f));
	LeanLeft->SetWorldRotation(FRotator(0.f, 0.f, -15.f));
	
	LeanRight = CreateDefaultSubobject<USceneComponent>(TEXT("LeanRight"));\
	LeanRight->SetupAttachment(RootComponent);
	LeanRight->SetWorldLocation(FVector(0.f, 40.f, 60.f));
	LeanRight->SetWorldRotation(FRotator(0.f, 0.f, 15.f));

	ThrowingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ThrowingPoint"));
	ThrowingPoint->SetupAttachment(FirstPersonCameraComponent);
	ThrowingPoint->SetWorldLocation(FVector(35.f, 30.f, -40.f));
	
	// Create CrouchTimelineComponent
	CrouchTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeLine"));

	// Create InteractComponent
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetPlayer(this);

	TeaseComponent = CreateDefaultSubobject<UTeaseSystem>(TEXT("TeaseComponent"));
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(false);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	Mesh1P->SetRelativeLocation(FVector(-5.f, 0.f, -155.f));


	CMC = GetCharacterMovement();
}

bool AHorrorTemplateCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation,
	int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible,
	int32* UserData) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
	FHitResult HitResult;

	FVector SocketLocation = GetMesh1P()->GetSocketLocation(PlayerData->AIVisionTargetBone);

	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, SocketLocation,
		FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
	NumberOfLoSChecksPerformed++;
	if (bHitSocket == false || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
	{
		OutSeenLocation = SocketLocation;
		OutSightStrength = 1;
		return true;
	}

	const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation(),
		FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
	NumberOfLoSChecksPerformed++;
	if (bHit == false || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;
		return true;
	}

	OutSightStrength = 0;
	return false;
}

void AHorrorTemplateCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (!IsValid(PlayerData)) return;

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerData->DefaultMappingContext, 0);
		}
	}

	FootstepInterval = PlayerData->WalkFootstepInterval;

	CMC->MaxWalkSpeed = PlayerData->WalkSpeed;
	PlayerData->JuiceFlaskAmount = 0;
	PlayerData->JuiceConsumedAmount = PlayerData->JuiceMaxConsumeAmount;
	PlayerData->CollectedCores.Empty();
	PlayerData->Stamina = PlayerData->MaxStamina;
	CanReplenishStamina = true;
	PlayerData->JuiceDiminishMultiplier = PlayerData->PassiveJuiceDiminishMultiplier;
	
	DefaultCameraLocation = SpringArmComponent->GetRelativeLocation();
	TargetCameraLocation = DefaultCameraLocation;

	FOnTimelineFloat CrouchValue;
	FOnTimelineEvent TimeLineFinishedEvent;

	CrouchValue.BindUFunction(this,	FName("TimeLineProgress"));
	TimeLineFinishedEvent.BindUFunction(this, FName("TimeLineFinished"));

	PlayerHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	CrouchHeight = CMC->GetCrouchedHalfHeight();

	if (PlayerData->CrouchCurve)
	{
		CrouchTimeLine->AddInterpFloat(PlayerData->CrouchCurve, CrouchValue);
	} 

	CrouchTimeLine->SetTimelineFinishedFunc(TimeLineFinishedEvent);
}

void AHorrorTemplateCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	const auto targetLoc = FMath::VInterpTo(SpringArmComponent->GetRelativeLocation(), TargetCameraLocation, DeltaSeconds, 5);
	SpringArmComponent->SetRelativeLocation(targetLoc);
	
	const auto rotTemp = FRotator(SpringArmComponent->GetRelativeRotation().Pitch, SpringArmComponent->GetRelativeRotation().Yaw, TargetRoll);
	const auto targetRot = FMath::RInterpTo(SpringArmComponent->GetRelativeRotation(), rotTemp, DeltaSeconds, 5);
	SpringArmComponent->SetRelativeRotation(targetRot);

	ReplenishStamina();
}

//////////////////////////////////////////////////////////////////////////// Input

void AHorrorTemplateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(PlayerData->SprintAction, ETriggerEvent::Triggered, this, &AHorrorTemplateCharacter::StartSprinting);
		EnhancedInputComponent->BindAction(PlayerData->SprintAction, ETriggerEvent::Completed, this, &AHorrorTemplateCharacter::StopSprinting);

		// Crouching
		EnhancedInputComponent->BindAction(PlayerData->CrouchAction, ETriggerEvent::Started, this, &AHorrorTemplateCharacter::CrouchLogic);

		// Moving
		EnhancedInputComponent->BindAction(PlayerData->MoveAction, ETriggerEvent::Triggered, this, &AHorrorTemplateCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(PlayerData->LookAction, ETriggerEvent::Triggered, this, &AHorrorTemplateCharacter::Look);
		
		EnhancedInputComponent->BindAction(PlayerData->LeanLeftAction, ETriggerEvent::Started, this, &AHorrorTemplateCharacter::OnLeanLeft);
		EnhancedInputComponent->BindAction(PlayerData->LeanLeftAction, ETriggerEvent::Completed, this, &AHorrorTemplateCharacter::OnLeanCompleted);
		// Interact
		EnhancedInputComponent->BindAction(PlayerData->InteractAndLeanRightAction, ETriggerEvent::Started, this, &AHorrorTemplateCharacter::OnLeanRight);
		EnhancedInputComponent->BindAction(PlayerData->InteractAndLeanRightAction, ETriggerEvent::Completed, this, &AHorrorTemplateCharacter::OnLeanCompleted);
		// Drink
		EnhancedInputComponent->BindAction(PlayerData->DrinkAction, ETriggerEvent::Triggered, this, &AHorrorTemplateCharacter::DrinkJuice);

		EnhancedInputComponent->BindAction(PlayerData->AttackAction, ETriggerEvent::Triggered, this, &AHorrorTemplateCharacter::StartAttack);
		EnhancedInputComponent->BindAction(PlayerData->AttackAction, ETriggerEvent::Completed, this, &AHorrorTemplateCharacter::FinalizeAttack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHorrorTemplateCharacter::ListenMechTrace()
{
}

void AHorrorTemplateCharacter::OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnLeanCompleted();
}

void AHorrorTemplateCharacter::AddJuice(float amount)
{
	PlayerData->JuiceFlaskAmount += amount;
	
	if (PlayerData->JuiceFlaskAmount > PlayerData->JuiceMaxFlaskAmount)
	{
		PlayerData->JuiceFlaskAmount = PlayerData->JuiceMaxFlaskAmount;
	}
	
}

void AHorrorTemplateCharacter::DrinkJuice()
{
	if (PlayerData->JuiceFlaskAmount > 0 && PlayerData->JuiceConsumedAmount < PlayerData->JuiceMaxConsumeAmount)
	{
		const auto temp = GetWorld()->GetDeltaSeconds() * PlayerData->JuiceDrinkSpeedMultiplier;
		PlayerData->JuiceFlaskAmount -= temp;
		PlayerData->JuiceConsumedAmount += temp;
	}
}

void AHorrorTemplateCharacter::JuiceChunk(float amount)
{
	if (PlayerData->JuiceConsumedAmount >= amount)
	{
		PlayerData->JuiceConsumedAmount -= amount;
	}
	else
	{
		PlayerData->JuiceConsumedAmount = 0;
	}
}

bool AHorrorTemplateCharacter::ConsumeJuice() const
{
	if (PlayerData->JuiceConsumedAmount > 0)
	{
		PlayerData->JuiceConsumedAmount -= GetWorld()->GetDeltaSeconds() * PlayerData->JuiceDiminishMultiplier;
		return false;
	}

	PlayerData->JuiceConsumedAmount = 0;
	return true;
}

void AHorrorTemplateCharacter::IsInSightJuiceDiminishChanger(bool IsInSight) const
{
	if (IsInSight)
	{
		PlayerData->JuiceDiminishMultiplier = PlayerData->SightJuiceDiminishMultiplier;
	}
	else
	{
		PlayerData->JuiceDiminishMultiplier = PlayerData->PassiveJuiceDiminishMultiplier;
	}
}

void AHorrorTemplateCharacter::AddCore(ACore* core)
{
	PlayerData->CollectedCores.Add(core);
}

void AHorrorTemplateCharacter::StaminaAction(float StaminaCost)
{
	if (PlayerData->Stamina >= StaminaCost)
	{
		PlayerData->Stamina -= StaminaCost;
	}
	else
	{
		PlayerData->Stamina = 0;
	}
}


void AHorrorTemplateCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AHorrorTemplateCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHorrorTemplateCharacter::CrouchLogic()
{
	if (!IsCrouching)
		StartCrouching();
	else
		StopCrouching();
}

void AHorrorTemplateCharacter::StartCrouching()
{
	IsCrouching = true;
	CMC->MaxWalkSpeed = PlayerData->CrouchSpeed;
	FootstepInterval = PlayerData->CrouchFootstepInterval;
	PlayerData->StaminaReplenishSpeed += 2.5;
	CrouchTimeLine->Play();
}

void AHorrorTemplateCharacter::StopCrouching()
{
	IsCrouching = false;
	CMC->MaxWalkSpeed = PlayerData->WalkSpeed;
	FootstepInterval = PlayerData->WalkFootstepInterval;
	PlayerData->StaminaReplenishSpeed -= 2.5;
	CrouchTimeLine->Reverse();
}


void AHorrorTemplateCharacter::TimeLineProgress(float Value) const
{
	const float newHeight = FMath::Lerp(PlayerHeight, CrouchHeight, Value);
	GetCapsuleComponent()->SetCapsuleHalfHeight(newHeight);
}

void AHorrorTemplateCharacter::TimeLineFinished() const
{
	if (CrouchTimeLine->GetPlaybackPosition() == 0.0f)
		GetCapsuleComponent()->SetCapsuleHalfHeight(PlayerHeight);
	else
		GetCapsuleComponent()->SetCapsuleHalfHeight(CrouchHeight);
}

void AHorrorTemplateCharacter::StartSprinting()
{
	if (IsCrouching)
		StopCrouching();
	else if (PlayerData->Stamina <= 0)
	{
		StopSprinting();
	}
	else
	{
		if (CMC->IsMovingOnGround())
		{
			UseStamina(0);
		}
		CanReplenishStamina = false;
		IsSprinting = true;
		CMC->MaxWalkSpeed = PlayerData->SprintSpeed;
		FootstepInterval = PlayerData->RunFootstepInterval;
	}

}

void AHorrorTemplateCharacter::StopSprinting()
{
	CanReplenishStamina = true;
	IsSprinting = false;
	CMC->MaxWalkSpeed = PlayerData->WalkSpeed;
	FootstepInterval = PlayerData->WalkFootstepInterval;
}

void AHorrorTemplateCharacter::OnLeanLeft()
{
	TargetCameraLocation = LeanLeft->GetRelativeLocation();
	TargetRoll = 360 + LeanLeft->GetComponentRotation().Roll;
}

void AHorrorTemplateCharacter::OnLeanRight()
{
	if (InteractComponent->HitInteractable)
	{
		InteractComponent->InteractCast();
	}
	else
	{
		TargetCameraLocation = LeanRight->GetRelativeLocation();
		TargetRoll = LeanRight->GetComponentRotation().Roll;
	}
}

void AHorrorTemplateCharacter::OnLeanCompleted()
{
	TargetCameraLocation = DefaultCameraLocation;
	TargetRoll = 0;
}

void AHorrorTemplateCharacter::UseStamina(float Amount)
{
	if (PlayerData->Stamina >= 0)
	{
		if (IsSprinting)
		{
			PlayerData->Stamina -= PlayerData->StaminaConsumeSpeed * GetWorld()->GetDeltaSeconds();
		}
	}
}

void AHorrorTemplateCharacter::ReplenishStamina()
{
	if (CanReplenishStamina)
	{
		if (PlayerData->Stamina < PlayerData->MaxStamina)
		{
			PlayerData->Stamina += PlayerData->StaminaReplenishSpeed * GetWorld()->GetDeltaSeconds();
		}
		else
		{
			PlayerData->Stamina = PlayerData->MaxStamina;
		}
			
	}
}

void AHorrorTemplateCharacter::StartAttack_Implementation()
{
}

void AHorrorTemplateCharacter::FinalizeAttack_Implementation()
{
}


