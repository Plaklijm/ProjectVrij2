// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableObject.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AThrowableObject::AThrowableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->InitialSpeed = 1200.f;
	ProjectileComponent->MaxSpeed = 1500.f;
	ProjectileComponent->ProjectileGravityScale = 2.f;
	ProjectileComponent->bShouldBounce = false;
}

// Called when the game starts or when spawned
void AThrowableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

