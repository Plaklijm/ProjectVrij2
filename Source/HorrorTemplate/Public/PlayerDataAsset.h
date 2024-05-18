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
	UInputAction* InteractAndLeanRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DrinkAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeanLeftAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float SprintSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float CrouchSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	UCurveFloat* CrouchCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float WalkFootstepInterval;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float RunFootstepInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float CrouchFootstepInterval;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Cores, meta=(AllowPrivateAccess = "true"))
	TArray<ACore*> CollectedCores;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceFlaskAmount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceConsumedAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceMaxFlaskAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceMaxConsumeAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float RootJuiceAddAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float RootJuiceReplenishSpeedMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Juice, meta=(AllowPrivateAccess = "true"))
	float JuiceDrinkSpeedMultiplier = 3;

public:
	UPlayerDataAsset() = default;
};
