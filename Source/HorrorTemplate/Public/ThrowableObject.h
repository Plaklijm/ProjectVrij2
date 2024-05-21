// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "ThrowableObject.generated.h"

class UProjectileMovementComponent;

UCLASS()
class HORRORTEMPLATE_API AThrowableObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileComponent;
public:
	// Sets default values for this actor's properties
	AThrowableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractPure(AHorrorTemplateCharacter* player) override;
	virtual void Interact_Implementation(AHorrorTemplateCharacter* player) override;
};
