// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Instance/MainGameInstance.h"

#include "SkillUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API USkillUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	float CoolTime;
	float RemaingTime;

	int SaveID = 0;

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CoolingBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountTime;

	UPROPERTY(meta = (BindWidget))
	class UImage* SkillIcon;

	UFUNCTION(BlueprintCallable)
	bool Ready() const;
	UFUNCTION(BlueprintCallable)
	void Use();
	UFUNCTION(BlueprintCallable)
	void SetSkill(int SkillID);

public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
};
