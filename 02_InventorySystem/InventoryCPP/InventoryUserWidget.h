// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Input/Reply.h"

#include "ItemUserWidget.h"
#include "InventoryComponent.h"

#include "InventoryUserWidget.generated.h"

DECLARE_DELEGATE(FDelegateUpdateInventory);

/**
 * 
 */
UCLASS()
class INVENTORYCPP_API UInventoryUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UItemUserWidget* Item_01;

	UPROPERTY(meta = (BindWidget))
	UItemUserWidget* Item_02;

	UPROPERTY(meta = (BindWidget))
	UItemUserWidget* Item_03;

	UPROPERTY(meta = (BindWidget))
	UItemUserWidget* Item_04;

	UPROPERTY(meta = (BindWidget))
	UItemUserWidget* Item_05;

	FDelegateUpdateInventory UpdateSelf;

public:
	void Set(int Index, int ItemID, int Count);

public:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	void Update(class UInventoryComponent* Record);
	void UpdateBack(class UInventoryComponent* Record);
};
