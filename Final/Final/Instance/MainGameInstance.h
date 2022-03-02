// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

// Items
public:
	TMap<int, FString> ItemsName;
	TMap<int, FString> ItemsIconPath;
	TMap<int, int> ItemsUsage;
	TMap<int, int> ItemsMaxNumberPerStack;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<int, class TSubclassOf<AActor>> ItemsMesh;

// Skills
public:
	TMap<int, FString> SkillsName;
	TMap<int, FString> SkillsIconPath;
	TMap<int, FString> SkillsVideoPath;
	TMap<int, float> SkillsCoolTime;
	TMap<int, int> SkillsNeedCoin;
	TMap<int, int> SkillsNeedDiamond;
	TMap<int, TSet<int>> SkillsNeedOtherSkills;
};
