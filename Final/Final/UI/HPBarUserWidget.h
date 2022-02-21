// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Components/ProgressBar.h"

#include "HPBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UHPBarUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	AActor* AttachedActor;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPProgressBar;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
