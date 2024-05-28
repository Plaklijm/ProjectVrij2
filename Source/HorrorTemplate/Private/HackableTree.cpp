// Fill out your copyright notice in the Description page of Project Settings.


#include "HackableTree.h"


// Sets default values
AHackableTree::AHackableTree()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHackableTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHackableTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHackableTree::InteractPure(AHorrorTemplateCharacter* player, float ElapsedSeconds)
{
}

void AHackableTree::Interact_Implementation(AHorrorTemplateCharacter* player, float ElapsedSeconds)
{
	IInteractInterface::Interact_Implementation(player, ElapsedSeconds);
}

void AHackableTree::StopInteract_Implementation(AHorrorTemplateCharacter* player)
{
	IInteractInterface::StopInteract_Implementation(player);
}

void AHackableTree::StopInteractPure(AHorrorTemplateCharacter* player)
{
}

