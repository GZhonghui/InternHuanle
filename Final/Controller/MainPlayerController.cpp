// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainUI = CreateWidget<UMainUserWidget>(GetWorld(), MainUIClass);
	MainUI->AddToViewport();

	InventoryUI = nullptr;
	InventoryVisibility = false;

	MenuUI = nullptr;
	MenuVisibility = false;

	SetShowMouseCursor(true);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainPlayerController::TriggerInventory);
	InputComponent->BindAction("Menu", IE_Pressed, this, &AMainPlayerController::TriggerMenu);
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto thisPlayer = Cast<AMainPlayerCharacter>(GetPawn());
	if (thisPlayer)
	{
		if (thisPlayer->AttackNumberValue)
		{
			MainUI->UpdateAttackNumer(thisPlayer->AttackNumberValue);
			MainUI->UpdateAttackTime(thisPlayer->AttackTimeValue);
		}
		else
		{
			MainUI->UpdateAttackNumer(0);
			MainUI->UpdateAttackTime(0);
		}
	}
}

void AMainPlayerController::TriggerInventory()
{
	if (MenuVisibility) return;

	InventoryVisibility = !InventoryVisibility;
	if (InventoryVisibility)
	{
		if (!InventoryUI) InventoryUI = CreateWidget<UInventoryUserWidget>(GetWorld(), InventoryUIClass);
		InventoryUI->AddToViewport();

		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		if(InventoryUI) InventoryUI->RemoveFromParent();

		SetInputMode(FInputModeGameOnly());
	}
}

void AMainPlayerController::TriggerMenu()
{
	MenuVisibility = !MenuVisibility;
	if (MenuVisibility)
	{
		if (!MenuUI) MenuUI = CreateWidget<UMenuUserWidget>(GetWorld(), MenuUIClass);
		MenuUI->AddToViewport();

		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		if (MenuUI) MenuUI->RemoveFromParent();

		SetInputMode(FInputModeGameOnly());
	}
}