// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
	Super::Init();
	// Usage:
	// 0: None
	// 1: Use
	// 2: Wear
	
	auto Set = [&](int ID, FString Name, FString IconPath, int Usage, int MaxNumber)
	{
		ItemsName.Emplace(ID, Name);
		ItemsIconPath.Emplace(ID, IconPath);
		ItemsUsage.Emplace(ID, Usage);
		ItemsMaxNumberPerStack.Emplace(ID, MaxNumber);
	};

	ItemsName.Emplace(0, TEXT(""));
	ItemsIconPath.Emplace(0, TEXT("/Game/0_Main/Texture/Pickup/Back_03_128"));

	ItemsName.Emplace(1, TEXT("Purple"));
	ItemsIconPath.Emplace(1, TEXT("/Game/0_Main/Texture/Pickup/Potion_1_128"));
	ItemsUsage.Emplace(1, 1);
	ItemsMaxNumberPerStack.Emplace(1, 3);

	ItemsName.Emplace(2, TEXT("Red"));
	ItemsIconPath.Emplace(2, TEXT("/Game/0_Main/Texture/Pickup/Potion_2_128"));
	ItemsUsage.Emplace(2, 1);
	ItemsMaxNumberPerStack.Emplace(2, 99);

	ItemsName.Emplace(3, TEXT("Yellow"));
	ItemsIconPath.Emplace(3, TEXT("/Game/0_Main/Texture/Pickup/Potion_3_128"));
	ItemsUsage.Emplace(3, 1);
	ItemsMaxNumberPerStack.Emplace(3, 99);

	Set(4, TEXT("Weapon_A"), TEXT("/Game/0_Main/Texture/Pickup/Weapon_A"), 2, 1);

	Set(5, TEXT("Weapon_B"), TEXT("/Game/0_Main/Texture/Pickup/Weapon_B"), 2, 1);
}