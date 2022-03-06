// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicServerGameMode.h"
#include "BasicServerHUD.h"
#include "BasicServerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABasicServerGameMode::ABasicServerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABasicServerHUD::StaticClass();
}
