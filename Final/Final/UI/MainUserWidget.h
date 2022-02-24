// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* AttackTimeProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AttackNumberTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImageCombo;

public:
	void UpdateAttackNumer(int Value);
	void UpdateAttackTime(float Value);

protected:
	float MessageRemainTime = 0;

public:
	void LogMessage(const FString& Text, float Time = 5.0f);

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
};
