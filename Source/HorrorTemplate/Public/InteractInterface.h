// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractInterface : public UInterface
{
	GENERATED_BODY()    
};

/**
 * 
 */
class HORRORTEMPLATE_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, Category="Interact")
	void Interact(AHorrorTemplateCharacter* player, float ElapsedSeconds);

	UFUNCTION()
	virtual void InteractPure(AHorrorTemplateCharacter* player, float ElapsedSeconds) = 0;
	
	UFUNCTION(BlueprintNativeEvent, Category="Interact")
	void StopInteract(AHorrorTemplateCharacter* player);

	UFUNCTION()
	virtual void StopInteractPure(AHorrorTemplateCharacter* player) = 0;
};
