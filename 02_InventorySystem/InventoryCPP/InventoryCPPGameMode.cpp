// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryCPPGameMode.h"
#include "InventoryCPPHUD.h"
#include "InventoryCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventoryCPPGameMode::AInventoryCPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AInventoryCPPHUD::StaticClass();
}
