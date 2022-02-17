// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_0216_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	AActor* AttachedActor;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPProgressBar;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
