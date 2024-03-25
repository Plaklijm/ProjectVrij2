// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorTemplateGameMode.h"
#include "HorrorTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorrorTemplateGameMode::AHorrorTemplateGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
