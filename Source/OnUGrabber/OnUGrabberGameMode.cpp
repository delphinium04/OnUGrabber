// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnUGrabberGameMode.h"
#include "OnUGrabberCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOnUGrabberGameMode::AOnUGrabberGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
