// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class AHorrorTemplateCharacter;
class APlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORTEMPLATE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool HitInteractable;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPlayer(AHorrorTemplateCharacter* Player);
	
	void InteractCast(float ElapsedSeconds);
	void StopInteractCast();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AHorrorTemplateCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere)
	APlayerController* FPController;
};
