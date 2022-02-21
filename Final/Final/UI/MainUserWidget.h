// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

public:
	void UpdateAttackNumer(int Value);
	void UpdateAttackTime(float Value);

	void LogMessage(const FString& Text);
};
