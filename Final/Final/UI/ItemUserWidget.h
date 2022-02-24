// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Instance/MainGameInstance.h"

#include "ItemUserWidget.generated.h"

DECLARE_DELEGATE(FInventoryUpdated);

DECLARE_DELEGATE_OneParam(FWearNewArms, int);

/**
 * 
 */
UCLASS()
class FINAL_API UItemUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FInventoryUpdated MeUpdated;

	FWearNewArms WearMe;

	UFUNCTION(BlueprintCallable)
	void UpdateArms();

protected:
	UFUNCTION(BlueprintCallable)
	void GetUpdate();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ImageIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNumber;

public:
	UPROPERTY(BlueprintReadWrite)
	int SaveID = 0;
	UPROPERTY(BlueprintReadWrite)
	int SaveNumber = 0;

public:
	void Set(int ItemID, int Count);

public:
	UFUNCTION(BlueprintCallable)
	int CanRightClick();

	UFUNCTION(BlueprintCallable)
	class TSubclassOf<AActor> GetWearableClass();

	UFUNCTION(BlueprintCallable)
	void UseOne();
};
