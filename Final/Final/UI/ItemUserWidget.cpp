// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUserWidget.h"

void UItemUserWidget::UpdateArms()
{
	WearMe.ExecuteIfBound(SaveID);
}

void UItemUserWidget::GetUpdate()
{
	MeUpdated.ExecuteIfBound();
}

void UItemUserWidget::Set(int ItemID, int Count)
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->ItemsName.Contains(ItemID))
		{
			FString ImagePath = GI->ItemsIconPath[ItemID];
			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));

			ImageIcon->SetBrushFromTexture(Texture);

			if (Count) ItemNumber->SetText(FText::FromString(FString::FromInt(Count)));
			else ItemNumber->SetText(FText::FromString(""));

			SaveID = ItemID;
			SaveNumber = Count;
		}
	}
}

int UItemUserWidget::CanRightClick()
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->ItemsName.Contains(SaveID) && SaveNumber && GI->ItemsUsage[SaveID])
		{
			return GI->ItemsUsage[SaveID];
		}
		else return 0;
	}

	return 0;
}

class TSubclassOf<AActor> UItemUserWidget::GetWearableClass()
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	TSubclassOf<AActor> EmptyResult;

	if (GI)
	{
		if (GI->ItemsMesh.Contains(SaveID))
		{
			return GI->ItemsMesh[SaveID];
		}
		else return EmptyResult;
	}
	return EmptyResult;
}

void UItemUserWidget::UseOne()
{
	SaveNumber -= 1;
	MeUpdated.ExecuteIfBound();
}