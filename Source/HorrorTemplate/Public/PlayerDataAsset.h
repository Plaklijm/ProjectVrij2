// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core.h"
#include "Engine/DataAsset.h"
#include "PlayerDataAsset.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable, BlueprintType)
class HORRORTEMPLATE_API UPlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DrinkAction;
			
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float SprintSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float CrouchSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	UCurveFloat* CrouchCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Cores, meta=(AllowPrivateAccess = "true"))
	TArray<ACore*> CollectedCores;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceAmount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceConsumedAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float RootJuiceAddAmount = 0;

public:
	UPlayerDataAsset() = default;
};
