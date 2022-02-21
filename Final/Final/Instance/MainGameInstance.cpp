// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
	Super::Init();
	
	ItemsName.Emplace(1, TEXT("Purple"));
	ItemsName.Emplace(2, TEXT("Red"));
	ItemsName.Emplace(3, TEXT("Yellow"));

	ItemsIconPath.Emplace(1, TEXT("/Game/0_Main/Texture/Pickup/Potion_1_128"));
	ItemsIconPath.Emplace(2, TEXT("/Game/0_Main/Texture/Pickup/Potion_2_128"));
	ItemsIconPath.Emplace(3, TEXT("/Game/0_Main/Texture/Pickup/Potion_3_128"));
}