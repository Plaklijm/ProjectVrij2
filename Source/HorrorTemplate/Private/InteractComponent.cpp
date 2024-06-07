// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorTemplate/Public/InteractComponent.h"

#include "InteractInterface.h"
#include "KismetTraceUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "HorrorTemplate/HorrorTemplateCharacter.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FPController = GetWorld()->GetFirstPlayerController();
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!FPController) return; 
	
	const FVector Start = FPController->PlayerCameraManager->GetCameraLocation();
	FVector Rotation(FPController->GetControlRotation().Vector());
	const FVector End = Rotation * 200.f + Start;
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	FHitResult HitResult;
	
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 5, UEngineTypes::ConvertToTraceType(ECC_Camera),
		false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	// Set the HitInteractable bool for the logic inside of the blueprint
	if (HitResult.bBlockingHit)
	{
		if (auto Actor = HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				HitInteractable = true;
			}
		}
	}
	else
	{
		HitInteractable = false;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("Blocking Hit =: %s"), HitInteractable ? TEXT("true") : TEXT("false")));
}

void UInteractComponent::SetPlayer(AHorrorTemplateCharacter* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(Player->GetName()));
	
	if (Player != nullptr)
	{
		this->PlayerCharacter = Player; 
	}
	else
	{
		this->PlayerCharacter = nullptr;
	}
}

void UInteractComponent::InteractCast(float ElapsedSeconds)
{
	if (HitInteractable)
	{
		const FVector Start = FPController->PlayerCameraManager->GetCameraLocation();
		FVector Rotation(FPController->GetControlRotation().Vector());
		const FVector End = Rotation * 200.f + Start;
	
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());

		FHitResult HitResult;
		
		DrawDebugSweptSphere(GetWorld(), Start, End, 5, FColor::Purple, true);
		
		if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 5, UEngineTypes::ConvertToTraceType(ECC_Camera),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true))
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
			{
				Cast<IInteractInterface>(HitResult.GetActor())->InteractPure(Cast<AHorrorTemplateCharacter>(GetOwner()), ElapsedSeconds);
				IInteractInterface::Execute_Interact(HitResult.GetActor(), Cast<AHorrorTemplateCharacter>(GetOwner()), ElapsedSeconds);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("IteractInterface Not Found"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Sphere Trace came back empty"));
		}
		
	}
}

void UInteractComponent::StopInteractCast()
{
	if (HitInteractable)
	{
		const FVector Start = FPController->PlayerCameraManager->GetCameraLocation();
		FVector Rotation(FPController->GetControlRotation().Vector());
		const FVector End = Rotation * 200.f + Start;
	
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());

		FHitResult HitResult;
	
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 5, UEngineTypes::ConvertToTraceType(ECC_Camera),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			Cast<IInteractInterface>(HitResult.GetActor())->StopInteractPure(Cast<AHorrorTemplateCharacter>(GetOwner()));
			IInteractInterface::Execute_StopInteract(HitResult.GetActor(), Cast<AHorrorTemplateCharacter>(GetOwner()));
		}
	}
}
