// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "../Instance/MainGameInstance.h"

#include "ArmsUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UArmsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int KeepingArms = 0;

	void UpdateWithSelf();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ImageIcon;

	UFUNCTION(BlueprintCallable)
	void SetNewArms(int NewArms);
};
