// Fill out your copyright notice in the Description page of Project Settings.

#include "MainUserWidget.h"

void UMainUserWidget::UpdateAttackNumer(int Value)
{
	auto ShowText = FString::Printf(TEXT("Combo Hit: %02d"), Value);
	AttackNumberTextBlock->SetText(FText::FromString(ShowText));

	FString ImagePath;
	
	// HARD CODE
	if (Value >= 8)
	{
		ImagePath = TEXT("/Game/0_Main/Texture/Combo/Combo_4");
	}
	else if (Value >= 6)
	{
		ImagePath = TEXT("/Game/0_Main/Texture/Combo/Combo_3");
	}
	else if (Value >= 4)
	{
		ImagePath = TEXT("/Game/0_Main/Texture/Combo/Combo_2");
	}
	else if (Value >= 2)
	{
		ImagePath = TEXT("/Game/0_Main/Texture/Combo/Combo_1");
	}

	if (Value >= 2)
	{
		UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));
		ImageCombo->SetBrushFromTexture(Texture);
		ImageCombo->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ImageCombo->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainUserWidget::UpdateAttackTime(float Value)
{
	AttackTimeProgressBar->SetPercent(Value);

	if (Value < 1e-4)
	{
		AttackNumberTextBlock->SetVisibility(ESlateVisibility::Hidden);
		AttackTimeProgressBar->SetVisibility(ESlateVisibility::Hidden);

		ImageCombo->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		AttackNumberTextBlock->SetVisibility(ESlateVisibility::Visible);
		AttackTimeProgressBar->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainUserWidget::LogMessage(const FString& Text, float Time)
{
	MessageText->SetVisibility(ESlateVisibility::Visible);

	MessageText->SetText(FText::FromString(Text));

	MessageRemainTime = Time;
}

void UMainUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	MessageRemainTime -= DeltaTime;
	if (MessageRemainTime < 0)
	{
		MessageRemainTime = -1;
		MessageText->SetVisibility(ESlateVisibility::Hidden);
	}
}