// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUserWidget.h"

void UMainUserWidget::UpdateAttackNumer(int Value)
{
	auto ShowText = FString::Printf(TEXT("Attack: %02d"), Value);
	AttackNumberTextBlock->SetText(FText::FromString(ShowText));
}

void UMainUserWidget::UpdateAttackTime(float Value)
{
	AttackTimeProgressBar->SetPercent(Value);
}

void UMainUserWidget::LogMessage(const FString& Text)
{
	MessageText->SetText(FText::FromString(Text));
}