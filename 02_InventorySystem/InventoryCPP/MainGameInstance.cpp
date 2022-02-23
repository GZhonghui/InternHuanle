// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
	Super::Init();

	ItemNames.Emplace(0, TEXT(""));
	ItemIconPaths.Emplace(0, TEXT("/Game/Texture/Back_03_128"));

	ItemNames.Emplace(1, TEXT("Apple"));
	ItemIconPaths.Emplace(1, TEXT("/Game/Texture/Potion_1_128"));

	ItemNames.Emplace(2, TEXT("Water"));
	ItemIconPaths.Emplace(2, TEXT("/Game/Texture/Potion_2_128"));

	ItemNames.Emplace(3, TEXT("Icon"));
	ItemIconPaths.Emplace(3, TEXT("/Game/Texture/Potion_3_128"));
}
