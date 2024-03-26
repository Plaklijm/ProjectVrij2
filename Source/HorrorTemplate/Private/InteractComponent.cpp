// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorTemplate/Public/InteractComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "HorrorTemplate/Public/InteractableComponent.h"

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
	const FVector End = Rotation * 150.f + Start;
	
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
			if (Actor->FindComponentByClass<UInteractableComponent>())
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

void UInteractComponent::Cast()
{
	if (HitInteractable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast!!"));
		const FVector Start = FPController->PlayerCameraManager->GetCameraLocation();
		FVector Rotation(FPController->GetControlRotation().Vector());
		const FVector End = Rotation * 150.f + Start;
	
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetOwner());

		FHitResult HitResult;
	
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 5, UEngineTypes::ConvertToTraceType(ECC_Camera),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

		if (auto Actor = HitResult.GetActor())
		{
			auto InteractableComponent = Actor->FindComponentByClass<UInteractableComponent>();
			if (InteractableComponent)
			{
				InteractableComponent->Execute();
			}
		}
	}
}
