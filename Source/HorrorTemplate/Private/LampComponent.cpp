// Fill out your copyright notice in the Description page of Project Settings.


#include "LampComponent.h"

#include "Engine/SpotLight.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
ULampComponent::ULampComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/*
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterMesh1P"));
	MeshComponent->bCastDynamicShadow = false;
	MeshComponent->CastShadow = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(MeshComponent);
	SpringArmComponent->TargetArmLength = 0;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f)); // Position the camera
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 25.f;
	SpringArmComponent->CameraLagSpeed = 25.f;

	SpotLight = CreateDefaultSubobject<ASpotLight>(TEXT("SpringArmComponent"));
	SpotLight->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);*/
}


// Called when the game starts
void ULampComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULampComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

