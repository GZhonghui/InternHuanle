// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"

void UInventoryUserWidget::Set(int Index, int ItemID, int Count)
{
	class UItemUserWidget* Items[]
	{
		nullptr,
		Item_01, Item_02, Item_03, Item_04, Item_05
	};
	Items[Index]->Set(ItemID, Count);
}

FReply UInventoryUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("Z"))
	{
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->SetShowMouseCursor(false);
			PlayerController->SetInputMode(FInputModeGameOnly());
		}

		RemoveFromParent();
	}

	return FReply::Handled();
}

void UInventoryUserWidget::Update(class UInventoryComponent* Record)
{
	for (int i = 1; i <= Record->MaxStack; i += 1)
	{
		if (Record->StackNumber[i])
		{
			Set(i, Record->StackID[i], Record->StackNumber[i]);
		}
		else
		{
			Set(i, 0, 0);
		}
	}
}

void UInventoryUserWidget::UpdateBack(class UInventoryComponent* Record)
{
	class UItemUserWidget* Items[]
	{
		nullptr,
		Item_01, Item_02, Item_03, Item_04, Item_05
	};
	for (int i = 1; i <= Record->MaxStack; i += 1)
	{
		Record->StackID[i] = Items[i]->ItemIDData;
		Record->StackNumber[i] = Items[i]->ItemNumberData;
	}
}