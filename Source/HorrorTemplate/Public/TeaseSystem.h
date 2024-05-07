// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TeaseSystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORTEMPLATE_API UTeaseSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTeaseSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Settings, meta=(AllowPrivateAccess = "true"))
	FVector TeaseBoxOuterExtends;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Settings, meta=(AllowPrivateAccess = "true"))
	FVector TeaseBoxInnerExtends;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Settings, meta=(AllowPrivateAccess = "true"))
	bool DrawDebug;
};
