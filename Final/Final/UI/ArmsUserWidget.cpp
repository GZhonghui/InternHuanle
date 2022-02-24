// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmsUserWidget.h"

void UArmsUserWidget::UpdateWithSelf()
{
	SetNewArms(KeepingArms);
}

void UArmsUserWidget::SetNewArms(int NewArms)
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if ((GI->ItemsName.Contains(NewArms) &&
			 GI->ItemsUsage.Contains(NewArms) &&
			 GI->ItemsUsage[NewArms] == 2) ||
			NewArms == 0)
		{
			FString ImagePath = GI->ItemsIconPath[NewArms];
			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));

			ImageIcon->SetBrushFromTexture(Texture);

			KeepingArms = NewArms;
		}
	}
}