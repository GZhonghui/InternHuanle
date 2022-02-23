// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "MainGameInstance.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "ItemUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCPP_API UItemUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNumber;

public:
	UPROPERTY(BlueprintReadWrite)
	int ItemIDData;

	UPROPERTY(BlueprintReadWrite)
	int ItemNumberData;

public:
	void Set(int ItemID, int Count);
};
