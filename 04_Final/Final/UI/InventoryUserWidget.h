// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Instance/MainGameInstance.h"

#include "../Component/PackageComponent.h"

#include "ItemUserWidget.h"
#include "ArmsUserWidget.h"

#include "InventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateItems();
	void UpdateBack();

protected:
	void Set(int Index, int ItemID, int Count);

	void WearNewArms(int ItemID);

public:
	virtual bool Initialize() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_01;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_02;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_03;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_04;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_05;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_06;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_07;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_08;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_09;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_10;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_11;

	UPROPERTY(meta = (BindWidget))
	class UItemUserWidget* Item_12;

	UPROPERTY(meta = (BindWidget))
	class UArmsUserWidget* Arms_01;

	UPROPERTY(meta = (BindWidget))
	class UArmsUserWidget* Arms_02;

	UPROPERTY(meta = (BindWidget))
	class UArmsUserWidget* Arms_03;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoinText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DiamondText;

public:
	void UpdateCoin(int Value);
	void UpdateDiamond(int Value);

public:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
};
