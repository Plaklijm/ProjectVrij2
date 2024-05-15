// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ListenMechanic.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UListenMechanic : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORTEMPLATE_API IListenMechanic
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="Interact")
	void FadeIn();

	UFUNCTION()
	virtual void FadeInPure() = 0;

	UFUNCTION(BlueprintNativeEvent, Category="Interact")
	void FadeOut();

	UFUNCTION()
	virtual void FadeOutPure() = 0;
};
