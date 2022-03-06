// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BasicServerHUD.generated.h"

UCLASS()
class ABasicServerHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABasicServerHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

