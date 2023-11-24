// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"

#include "../Instance/MainGameInstance.h"

#include "SkillTreeItemUserWidget.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FPreviewNewSkill, int);

UCLASS()
class FINAL_API USkillTreeItemUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	int SaveID; // Skill ID

	UPROPERTY(meta = (BindWidget))
	class UImage* SkillIcon;

public:
	void SetNewSkill(int NewSkillID);

public:
	FPreviewNewSkill PreviewMe;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
