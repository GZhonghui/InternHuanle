// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Instance/MainGameInstance.h"

#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AllText;

public:
	void UpdateItems(const TMap<int, int>& Items);

protected:
	void Set(int Index, int ItemID, int Count);

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_01;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_02;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_03;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_04;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_05;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_06;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_07;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_08;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_09;

	UPROPERTY(meta = (BindWidget))
	class UImage* Pickup_10;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_01;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_02;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_03;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_04;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_05;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_06;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_07;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_08;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_09;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number_10;
};
