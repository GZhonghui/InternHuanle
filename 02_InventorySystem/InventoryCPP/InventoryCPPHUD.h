// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryCPPHUD.generated.h"

UCLASS()
class AInventoryCPPHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInventoryCPPHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

