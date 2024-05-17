// Fill out your copyright notice in the Description page of Project Settings.


#include "Soup.h"


// Sets default values
ASoup::ASoup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASoup::Interact_Implementation(AHorrorTemplateCharacter* player)
{
	IInteractInterface::Interact_Implementation(player);
}

void ASoup::InteractPure(AHorrorTemplateCharacter* player)
{
	
}

void ASoup::FadeIn_Implementation()
{
	IListenMechanic::FadeIn_Implementation();
}

void ASoup::FadeOut_Implementation()
{
	IListenMechanic::FadeOut_Implementation();
}

void ASoup::FadeInPure()
{
}

void ASoup::FadeOutPure()
{
}

