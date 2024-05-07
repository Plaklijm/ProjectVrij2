// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaseSystem.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UTeaseSystem::UTeaseSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeaseSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTeaseSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto Point = UKismetMathLibrary::RandomPointInBoundingBox(GetOwner()->GetActorLocation(), TeaseBoxOuterExtends);


	const auto Box = FBox::BuildAABB(GetOwner()->GetActorLocation(), TeaseBoxInnerExtends);

	if (DrawDebug)
	{
		DrawDebugBox(GetWorld(), GetOwner()->GetActorLocation(), TeaseBoxOuterExtends, FColor::Orange);
		DrawDebugBox(GetWorld(), GetOwner()->GetActorLocation(), TeaseBoxInnerExtends, FColor::Yellow);

		if (!Box.IsInside(Point))
		{
			DrawDebugSphere(GetWorld(), Point, 2, 12, FColor::Purple);
		}

	}

	// ...
}


