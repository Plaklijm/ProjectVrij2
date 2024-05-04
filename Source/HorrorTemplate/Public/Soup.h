// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Soup.generated.h"

UCLASS()
class HORRORTEMPLATE_API ASoup : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASoup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AHorrorTemplateCharacter* player) override;
	
	virtual void InteractPure(AHorrorTemplateCharacter* player) override;
};
