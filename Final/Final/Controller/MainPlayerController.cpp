// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainUI = CreateWidget<UMainUserWidget>(GetWorld(), MainUIClass);
	MainUI->AddToViewport();

	InventoryUI = nullptr;
	MenuUI = nullptr;

	SetShowMouseCursor(true);

	MainUI->LogMessage(TEXT("Game Started"));

	auto thisPlayer = Cast<AMainPlayerCharacter>(GetPawn());
	if (thisPlayer)
	{
		thisPlayer->LogMyMessage.BindUObject(MainUI, &UMainUserWidget::LogMessage);
	}
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
	InventoryUI = CreateWidget<UInventoryUserWidget>(GetWorld(), InventoryUIClass);
	InventoryUI->AddToViewport();

	auto PlayerCharacter = Cast<AMainPlayerCharacter>(GetPawn());
	if (PlayerCharacter) InventoryUI->UpdateItems();

	InventoryUI->bIsFocusable = true;
	InventoryUI->SetFocus();
	InventoryUI->SetKeyboardFocus();

	FInputModeUIOnly UIMode;
	UIMode.SetWidgetToFocus(InventoryUI->TakeWidget());

	SetInputMode(UIMode);
}

void AMainPlayerController::TriggerMenu()
{
	MenuUI = CreateWidget<UMenuUserWidget>(GetWorld(), MenuUIClass);
	MenuUI->AddToViewport();

	MenuUI->bIsFocusable = true;
	MenuUI->SetFocus();
	MenuUI->SetKeyboardFocus();

	FInputModeUIOnly UIMode;
	UIMode.SetWidgetToFocus(MenuUI->TakeWidget());

	SetInputMode(UIMode);

	SetPause(true);
}