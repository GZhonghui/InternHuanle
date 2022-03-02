// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

#include "SkillTreeItemUserWidget.h"

#include "SkillTreeUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API USkillTreeUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_01;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_02;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_03;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_04;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_05;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_06;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_07;

	UPROPERTY(meta = (BindWidget))
	class USkillTreeItemUserWidget* SkillTreeItem_08;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillDes;

public:
	void PreviewASkill(int SkillID);

public:
	virtual bool Initialize() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
};
