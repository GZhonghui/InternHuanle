// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../UI/MainUserWidget.h"
#include "../UI/InventoryUserWidget.h"
#include "../UI/MenuUserWidget.h"

#include "../Character/MainPlayerCharacter.h"

#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UMainUserWidget> MainUIClass;
	class UMainUserWidget* MainUI;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<UInventoryUserWidget> InventoryUIClass;
	class UInventoryUserWidget* InventoryUI;

	UPROPERTY(EditAnywhere)
	class TSubclassOf<UMenuUserWidget> MenuUIClass;
	class UMenuUserWidget* MenuUI;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

protected:
	bool InventoryVisibility;
	void TriggerInventory();

	bool MenuVisibility;
	void TriggerMenu();
};
