// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InventoryCPPCharacter.h"
#include "InventoryUserWidget.h"

#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCPP_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

public:
	void TriggerInventory();

protected:
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UInventoryUserWidget> InventoryUIClass;
	class UInventoryUserWidget* InventoryUI;
};
