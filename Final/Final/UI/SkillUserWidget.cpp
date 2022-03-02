// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillUserWidget.h"

bool USkillUserWidget::Ready() const
{
	return RemaingTime < 0.0f;
}

void USkillUserWidget::Use()
{
	if (!Ready()) return;

	RemaingTime = CoolTime;
}

void USkillUserWidget::SetSkill(int SkillID)
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->SkillsIconPath.Contains(SkillID))
		{
			FString ImagePath = GI->SkillsIconPath[SkillID];
			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));

			if(SkillIcon) SkillIcon->SetBrushFromTexture(Texture);
		}

		if (GI->SkillsCoolTime.Contains(SkillID))
		{
			CoolTime = GI->SkillsCoolTime[SkillID];
			RemaingTime = -1.0f;
		}

		SaveID = SkillID;
	}
}

bool USkillUserWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	CoolTime = 10.0f;
	RemaingTime = -1.0f;

	return true;
}

void USkillUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	RemaingTime -= DeltaTime;
	if (RemaingTime < 0.0f) RemaingTime = -1.0f;

	if (CoolingBar)
	{
		float P = FMath::Clamp(RemaingTime, 0.0f, CoolTime) / CoolTime;
		CoolingBar->SetPercent(P);
	}

	if (CountTime)
	{
		if (RemaingTime > 1.0f)
		{
			int R = FMath::FloorToInt(RemaingTime);
			CountTime->SetText(FText::FromString(FString::FromInt(R)));

			CountTime->SetVisibility(ESlateVisibility::Visible);
		}
		else if (RemaingTime > 0.1f)
		{
			FString R = FString::Printf(TEXT("%.1f"), RemaingTime);
			CountTime->SetText(FText::FromString(R));

			CountTime->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CountTime->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}