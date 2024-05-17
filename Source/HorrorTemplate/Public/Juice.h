// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "ListenMechanic.h"
#include "GameFramework/Actor.h"
#include "Juice.generated.h"

UCLASS()
class HORRORTEMPLATE_API AJuice : public AActor, public IInteractInterface, public IListenMechanic
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJuice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AHorrorTemplateCharacter* player) override;
	
	virtual void InteractPure(AHorrorTemplateCharacter* player) override;

	void FadeIn_Implementation() override;
	void FadeOut_Implementation() override;

	virtual void FadeInPure() override;
	virtual void FadeOutPure() override;
};
