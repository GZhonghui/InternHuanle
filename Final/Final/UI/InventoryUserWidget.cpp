// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"

void UInventoryUserWidget::UpdateItems(const TMap<int, int>& Items)
{
	 FString Content;

	 const TMap<int, FString>& Names = Cast<UMainGameInstance>(GetGameInstance())->ItemsName;

	 int Index = 0;

	for (auto& Item : Items)
	{
		if (Names.Contains(Item.Key))
		{
			auto NewLine = FString("Item: ") + Names[Item.Key] +
				FString(", Count: ") + FString::FromInt(Item.Value) + FString("\n");
			Content += NewLine;

			Set(++Index, Item.Key, Item.Value);
		}	
	}

	AllText->SetText(FText::FromString(Content));
}

void UInventoryUserWidget::Set(int Index, int ItemID, int Count)
{
	if (Index <= 0 || Index >= 11) return;

	const TMap<int, FString>& IconPath = Cast<UMainGameInstance>(GetGameInstance())->ItemsIconPath;
	
	if (!IconPath.Contains(ItemID)) return;

	FString ImagePath = IconPath[ItemID];
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));

	class UImage* PickupIcons[11] =
	{
		nullptr,
		Pickup_01, Pickup_02, Pickup_03, Pickup_04, Pickup_05,
		Pickup_06, Pickup_07, Pickup_08, Pickup_09, Pickup_10
	};

	class UTextBlock* PickupNumbers[11] =
	{
		nullptr,
		Number_01, Number_02, Number_03, Number_04, Number_05,
		Number_06, Number_07, Number_08, Number_09, Number_10
	};

	PickupIcons[Index]->SetBrushFromTexture(Texture);
	PickupNumbers[Index]->SetText(FText::FromString(FString::FromInt(Count)));
}