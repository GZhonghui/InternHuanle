// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
	Super::Init();
	
	// Init Item Table

	// Usage:
	// 0: None
	// 1: Use
	// 2: Wear

	auto SetItem = [&](int ID, FString Name, FString IconPath, int Usage, int MaxNumber)
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

	SetItem(4, TEXT("Weapon_A"), TEXT("/Game/0_Main/Texture/Pickup/Weapon_A"), 2, 1);

	SetItem(5, TEXT("Weapon_B"), TEXT("/Game/0_Main/Texture/Pickup/Weapon_B"), 2, 1);

	// Init Skill Table

	auto SetSkill = [&](int ID, FString Name, FString IconPath, FString VideoPath, float CoolTime)
	{
		SkillsName.Emplace(ID, Name);
		SkillsIconPath.Emplace(ID, IconPath);
		SkillsVideoPath.Emplace(ID, VideoPath);
		SkillsCoolTime.Emplace(ID, CoolTime);
	};

	SetSkill(1, TEXT("Basic Fire Magic"), TEXT("/Game/0_Main/Texture/Skills/Fire_01"),
		TEXT("/Game/0_Main/Video/Skills/Fire_01_Video"), 3.0f);

	SetSkill(2, TEXT("Fire Mass"), TEXT("/Game/0_Main/Texture/Skills/Fire_02"),
		TEXT("/Game/0_Main/Video/Skills/Fire_02_Video"), 10.0f);

	SetSkill(3, TEXT("Basic Ice Magic"), TEXT("/Game/0_Main/Texture/Skills/Ice_01"),
		TEXT("/Game/0_Main/Video/Skills/Ice_01_Video"), 3.0f);

	SetSkill(4, TEXT("Ice Mass"), TEXT("/Game/0_Main/Texture/Skills/Ice_02"),
		TEXT("/Game/0_Main/Video/Skills/Ice_02_Video"), 12.0f);

	SetSkill(5, TEXT("Basic Light Magic"), TEXT("/Game/0_Main/Texture/Skills/Light_01"),
		TEXT("/Game/0_Main/Video/Skills/Light_01_Video"), 5.0f);

	SetSkill(6, TEXT("Light Mass"), TEXT("/Game/0_Main/Texture/Skills/Light_02"),
		TEXT("/Game/0_Main/Video/Skills/Light_02_Video"), 15.0f);

	SetSkill(7, TEXT("Basic Dark Magic"), TEXT("/Game/0_Main/Texture/Skills/Dark_01"),
		TEXT("/Game/0_Main/Video/Skills/Dark_01_Video"), 4.0f);

	SetSkill(8, TEXT("Dark Mass"), TEXT("/Game/0_Main/Texture/Skills/Dark_02"),
		TEXT("/Game/0_Main/Video/Skills/Dark_01_Video"), 18.0f);
}