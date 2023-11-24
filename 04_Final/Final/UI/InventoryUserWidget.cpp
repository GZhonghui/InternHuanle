// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUserWidget.h"

void UInventoryUserWidget::UpdateItems()
{
	auto Package = Cast<UPackageComponent>(GetOwningPlayer()->GetPawn()->GetComponentByClass(UPackageComponent::StaticClass()));
	if (Package)
	{
		for (int i = 1; i <= Package->MaxStack; i += 1)
		{
			if (Package->StackNumber[i])
			{
				Set(i, Package->StackID[i], Package->StackNumber[i]);
			}
			else
			{
				Set(i, 0, 0);
			}
		}

		// HARD CODE

		class UArmsUserWidget* ArmsItems[]
		{
			nullptr,
			Arms_01, Arms_02, Arms_03
		};
		for (int i = 1; i <= 3; i += 1)
		{
			ArmsItems[i]->UpdateWithSelf();
		}
	}
}

void UInventoryUserWidget::UpdateBack()
{
	auto Package = Cast<UPackageComponent>(GetOwningPlayer()->GetPawn()->GetComponentByClass(UPackageComponent::StaticClass()));

	class UItemUserWidget* Items[]
	{
		nullptr,
		Item_01, Item_02, Item_03, Item_04, Item_05,
		Item_06, Item_07, Item_08, Item_09, Item_10,
		Item_11, Item_12
	};

	if (Package)
	{
		for (int i = 1; i <= 12; i += 1) // HARD CODE
		{
			Package->StackID[i] = Items[i]->SaveID;
			Package->StackNumber[i] = Items[i]->SaveNumber;
		}

		UpdateItems();
	}
}

void UInventoryUserWidget::Set(int Index, int ItemID, int Count)
{
	class UItemUserWidget* Items[]
	{
		nullptr,
		Item_01, Item_02, Item_03, Item_04, Item_05,
		Item_06, Item_07, Item_08, Item_09, Item_10,
		Item_11, Item_12
	};

	if (Index <= 0 || Index >= 13) return; // HARD CODE

	Items[Index]->Set(ItemID, Count);
}

void UInventoryUserWidget::WearNewArms(int ItemID)
{
	Arms_01->SetNewArms(ItemID);
}

bool UInventoryUserWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	class UItemUserWidget* Items[]
	{
		nullptr,
		Item_01, Item_02, Item_03, Item_04, Item_05,
		Item_06, Item_07, Item_08, Item_09, Item_10,
		Item_11, Item_12
	};

	for (int i = 1; i <= 12; i += 1) //HARD CODE
	{
		Items[i]->MeUpdated.BindUObject(this, &UInventoryUserWidget::UpdateBack);
		Items[i]->WearMe.BindUObject(this, &UInventoryUserWidget::WearNewArms);
	}

	return true;
}

void UInventoryUserWidget::UpdateCoin(int Value)
{
	if (CoinText)
	{
		CoinText->SetText(FText::FromString(FString::Printf(TEXT("Coin: %d"), Value)));
	}
}

void UInventoryUserWidget::UpdateDiamond(int Value)
{
	if (DiamondText)
	{
		DiamondText->SetText(FText::FromString(FString::Printf(TEXT("Diamond: %d"), Value)));
	}
}

FReply UInventoryUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("X"))
	{
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
		}

		RemoveFromParent();
	}

	return FReply::Handled();
}

void UInventoryUserWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	SetFocus();
	SetKeyboardFocus();
}