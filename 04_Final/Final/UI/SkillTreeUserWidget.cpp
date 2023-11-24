#include "SkillTreeUserWidget.h"

void USkillTreeUserWidget::PreviewASkill(int SkillID)
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->SkillsName.Contains(SkillID))
		{
			SkillDes->SetText(FText::FromString(GI->SkillsName[SkillID]));
		}
	}
}

bool USkillTreeUserWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	class USkillTreeItemUserWidget* SkillItems[]
	{
		nullptr,
		SkillTreeItem_01, SkillTreeItem_02, SkillTreeItem_03, SkillTreeItem_04,
		SkillTreeItem_05, SkillTreeItem_06, SkillTreeItem_07, SkillTreeItem_08
	};

	// HARD CODE
	for (int i = 1; i <= 8; i += 1)
	{
		if (SkillItems[i])
		{
			SkillItems[i]->SetNewSkill(i);
			SkillItems[i]->PreviewMe.BindUObject(this, &USkillTreeUserWidget::PreviewASkill);
		}
	}

	return true;
}

FReply USkillTreeUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("V"))
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

void USkillTreeUserWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	SetFocus();
	SetKeyboardFocus();
}