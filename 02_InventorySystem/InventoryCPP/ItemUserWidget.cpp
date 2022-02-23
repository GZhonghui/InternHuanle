// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUserWidget.h"

void UItemUserWidget::Set(int ItemID, int Count)
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->ItemNames.Contains(ItemID))
		{
			FString ImagePath = GI->ItemIconPaths[ItemID];
			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));

			ItemIcon->SetBrushFromTexture(Texture);

			if(Count) ItemNumber->SetText(FText::FromString(FString::FromInt(Count)));
			else ItemNumber->SetText(FText::FromString(""));

			ItemIDData = ItemID;
			ItemNumberData = Count;
		}
	}
}