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

void AJuice::Interact_Implementation(AHorrorTemplateCharacter* player, float ElapsedSeconds)
{
	IInteractInterface::Interact_Implementation(player, ElapsedSeconds);
}

void AJuice::InteractPure(AHorrorTemplateCharacter* player, float ElapsedSeconds)
{
	
}

void AJuice::StopInteract_Implementation(AHorrorTemplateCharacter* player)
{
	IInteractInterface::StopInteract_Implementation(player);
}

void AJuice::StopInteractPure(AHorrorTemplateCharacter* player)
{
}



