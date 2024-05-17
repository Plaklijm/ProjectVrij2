// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorTemplate/Public/Core.h"


// Sets default values
ACore::ACore()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACore::Interact_Implementation(AHorrorTemplateCharacter* player)
{
	IInteractInterface::Interact_Implementation(player);
}

void ACore::InteractPure(AHorrorTemplateCharacter* player)
{
	
}

void ACore::FadeIn_Implementation()
{
	IListenMechanic::FadeIn_Implementation();
}

void ACore::FadeOut_Implementation()
{
	IListenMechanic::FadeOut_Implementation();
}

void ACore::FadeInPure()
{
}

void ACore::FadeOutPure()
{
}

