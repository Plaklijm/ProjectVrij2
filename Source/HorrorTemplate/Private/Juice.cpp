// Fill out your copyright notice in the Description page of Project Settings.


#include "Juice.h"


// Sets default values
AJuice::AJuice()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJuice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJuice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJuice::Interact_Implementation(AHorrorTemplateCharacter* player)
{
	IInteractInterface::Interact_Implementation(player);

	GEngine->AddOnScreenDebugMessage( -1,1.0,FColor::Red, TEXT("Hello From C++ Juice"));
}

void AJuice::InteractPure(AHorrorTemplateCharacter* player)
{
	
}

void AJuice::FadeIn_Implementation()
{
	IListenMechanic::FadeIn_Implementation();
}

void AJuice::FadeOut_Implementation()
{
	IListenMechanic::FadeOut_Implementation();
}

void AJuice::FadeInPure()
{
}

void AJuice::FadeOutPure()
{
}


