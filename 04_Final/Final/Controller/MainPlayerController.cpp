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

	bEnableMouseOverEvents = true;
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMainPlayerController::TriggerInventory);
	InputComponent->BindAction("Menu", IE_Pressed, this, &AMainPlayerController::TriggerMenu);
	InputComponent->BindAction("SkillTree", IE_Pressed, this, &AMainPlayerController::TriggerSkillTree);

	InputComponent->BindAction("SkillQ", IE_Pressed, this, &AMainPlayerController::UseSkillQ);
	InputComponent->BindAction("SkillE", IE_Pressed, this, &AMainPlayerController::UseSkillE);
	InputComponent->BindAction("SkillR", IE_Pressed, this, &AMainPlayerController::UseSkillR);
	InputComponent->BindAction("SkillF", IE_Pressed, this, &AMainPlayerController::UseSkillF);
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

void AMainPlayerController::UseSkillQ()
{
	if (MainUI && MainUI->Skill_Q)
	{
		MainUI->Skill_Q->Use();
		MainUI->LogMessage(TEXT("Q!"));
	}
}

void AMainPlayerController::UseSkillE()
{
	if (MainUI && MainUI->Skill_E)
	{
		MainUI->Skill_E->Use();
		MainUI->LogMessage(TEXT("E!"));
	}
}

void AMainPlayerController::UseSkillR()
{
	if (MainUI && MainUI->Skill_R)
	{
		MainUI->Skill_R->Use();
		MainUI->LogMessage(TEXT("R!"));
	}
}

void AMainPlayerController::UseSkillF()
{
	if (MainUI && MainUI->Skill_F)
	{
		MainUI->Skill_F->Use();
		MainUI->LogMessage(TEXT("F!"));
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

void AMainPlayerController::TriggerSkillTree()
{
	SkillTreeUI = CreateWidget<USkillTreeUserWidget>(GetWorld(), SkillTreeUIClass);
	SkillTreeUI->AddToViewport();

	SkillTreeUI->bIsFocusable = true;
	SkillTreeUI->SetFocus();
	SkillTreeUI->SetKeyboardFocus();

	FInputModeUIOnly UIMode;
	UIMode.SetWidgetToFocus(SkillTreeUI->TakeWidget());

	SetInputMode(UIMode);
}