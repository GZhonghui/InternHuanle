// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/ProgressBar.h"

void UEnemyHealthWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}

	FVector2D ScreenPosition;
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),
		AttachedActor->GetActorLocation() + FVector(0, 0, 100), ScreenPosition);
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
