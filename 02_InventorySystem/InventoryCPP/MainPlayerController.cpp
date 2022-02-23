// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainPlayerController::TriggerInventory);

	InventoryUI = nullptr;
}

void AMainPlayerController::TriggerInventory()
{
	InventoryUI = CreateWidget<UInventoryUserWidget>(this, InventoryUIClass);

	auto ThisPlayer = Cast<AInventoryCPPCharacter>(GetPawn());
	if (ThisPlayer)
	{
		InventoryUI->Update(ThisPlayer->Inventory);
	}

	InventoryUI->AddToViewport();

	//InventoryUI->bIsFocusable = true;
	//InventoryUI->SetKeyboardFocus();
	//InventoryUI->SetFocus();

	SetShowMouseCursor(true);
	
	FInputModeUIOnly UIMode;
	UIMode.SetWidgetToFocus(InventoryUI->TakeWidget());
	//SetInputMode(UIMode);
}