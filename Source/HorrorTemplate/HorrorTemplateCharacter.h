// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "HorrorTemplateCharacter.generated.h"

class UPlayerDataAsset;
class UInteractComponent;
class UTimelineComponent;
class USpringArmComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCharacterMovementComponent;
class UCameraComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHorrorTemplateCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UInteractComponent* InteractComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Settings, meta=(AllowPrivateAccess = "true"))
	UPlayerDataAsset* PlayerData;
	
	UPROPERTY(VisibleAnywhere)
	UCharacterMovementComponent* CMC;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	float PlayerHeight;
	
	UPROPERTY(VisibleAnywhere, Category=Movement)
	float CrouchHeight;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	bool IsCrouching;
	
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* CrouchTimeLine;

public:
	AHorrorTemplateCharacter();

protected:
	virtual void BeginPlay();

public:

	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void CrouchLogic();
	void StartCrouching();
	void StopCrouching();
	
	void StartSprinting();
	void StopSprinting();

	UFUNCTION()
	void TimeLineProgress(float Value) const;

	UFUNCTION()
	void TimeLineFinished() const;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

