// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillTreeItemUserWidget.h"

void USkillTreeItemUserWidget::SetNewSkill(int NewSkillID)
{
	auto GI = Cast<UMainGameInstance>(GetGameInstance());

	if (GI)
	{
		if (GI->SkillsIconPath.Contains(NewSkillID))
		{
			FString ImagePath = GI->SkillsIconPath[NewSkillID];
			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(ImagePath)));

			SkillIcon->SetBrushFromTexture(Texture);

			SaveID = NewSkillID;
		}
	}
}

FReply USkillTreeItemUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown("LeftMouseButton"))
	{
		PreviewMe.ExecuteIfBound(SaveID);
	}

	return FReply::Handled();
}