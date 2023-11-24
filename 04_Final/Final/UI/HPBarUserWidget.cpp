// Fill out your copyright notice in the Description page of Project Settings.

#include "HPBarUserWidget.h"

void UHPBarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}

	FVector2D ScreenPosition;
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),
		AttachedActor->GetActorLocation() + FVector(0, 0, 128), ScreenPosition);
	if (bIsOnScreen)
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;
		if (HPProgressBar)
		{
			HPProgressBar->SetRenderTranslation(ScreenPosition);
			
		}
	}
}