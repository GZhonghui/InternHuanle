// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../HeroCharacter.h"

#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_0216_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void Change();

	int CurrentHero = 0;

	UPROPERTY(EditAnywhere)
	TArray<class TSubclassOf<AHeroCharacter>> newHeroClass;
};
