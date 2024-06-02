// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Public/Core.h"
#include "HorrorTemplateCharacter.generated.h"

struct FInputActionInstance;
class UInputAction;
class ULampComponent;
class UTeaseSystem;
class UPlayerDataAsset;
class UInteractComponent;
class UTimelineComponent;
class USpringArmComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCharacterMovementComponent;
class USceneComponent;
class USphereComponent;
class UCameraComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHorrorTemplateCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PlayerRootComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CameraCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) 
	UInteractComponent* InteractComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UTeaseSystem* TeaseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	USceneComponent* LeanLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	USceneComponent* LeanRight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ThrowingPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Settings, meta=(AllowPrivateAccess = "true"))
	UPlayerDataAsset* PlayerData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCharacterMovementComponent* CMC;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	float PlayerHeight;
	
	UPROPERTY(VisibleAnywhere, Category=Movement)
	float CrouchHeight;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	float NewHeight;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	bool CanReplenishStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float FootstepInterval;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	bool IsSprinting;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	bool IsCrouching;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	FVector DefaultCameraLocation;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	FVector TargetCameraLocation;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	float TargetRoll;
	
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* CrouchTimeLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	bool EnablePlayerInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool IsInCave;
	
public:
	AHorrorTemplateCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:

	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
 
	void CrouchLogic();
	void StartCrouching();
	void StopCrouching();
	
	void StartSprinting();
	void StopSprinting();

	void OnLeanLeft();
	void OnLeanRight();
	void OnLeanCompleted();

	void OnInteract(const FInputActionInstance& Instance);
	void OnStopInteract();

	void UseStamina(float Amount);
	void ReplenishStamina();

	UFUNCTION(BlueprintNativeEvent)
	void StartAttack();

	UFUNCTION(BlueprintNativeEvent)
	void FinalizeAttack();
	
	UFUNCTION()
	void TimeLineProgress(float Value);

	UFUNCTION()
	void TimeLineFinished() const;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	void ListenMechTrace();

	UFUNCTION()
	void OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintCallable)
	void AddJuice(float amount);

	UFUNCTION(BlueprintCallable)
	void DrinkJuice();

	UFUNCTION(BlueprintCallable)
	void JuiceChunk(float amount);

	UFUNCTION(BlueprintCallable)
	int ConsumeJuice() const;

	UFUNCTION(BlueprintCallable)
	void HandleInsanity(int JuiceState);

	UFUNCTION(BlueprintCallable)
	void IsInSightJuiceDiminishChanger(bool IsInSight) const;
	
	UFUNCTION(BlueprintCallable)
	void AddCore(ACore* core);

	UFUNCTION(BlueprintCallable)
	void StaminaAction(float StaminaCost);

	UFUNCTION(BlueprintCallable)
	void SetIsInCave(bool NewValue);

	UFUNCTION(BlueprintNativeEvent)
	void GardenerEvent(bool SetActive);
	
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

