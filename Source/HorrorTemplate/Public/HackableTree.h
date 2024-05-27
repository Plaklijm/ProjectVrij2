// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "HackableTree.generated.h"

UCLASS()
class HORRORTEMPLATE_API AHackableTree : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHackableTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractPure(AHorrorTemplateCharacter* player, float ElapsedSeconds) override;
	virtual void Interact_Implementation(AHorrorTemplateCharacter* player, float ElapsedSeconds) override;
	
	virtual void StopInteract_Implementation(AHorrorTemplateCharacter* player) override;

	virtual void StopInteractPure(AHorrorTemplateCharacter* player) override;
};
