// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "../UI/HPBarUserWidget.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	showHPBar = true;

	static ConstructorHelpers::FClassFinder<UHPBarUserWidget> HPBarBPClass(TEXT("/Game/0_Main/UI/BP_HPBarUI.BP_HPBarUI_C"));
	HPBarClass = HPBarBPClass.Class;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = HealthMax = 100;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ApplyHealthChange(float Value)
{
	Health = FMath::Clamp(Health + Value, 0.0f, HealthMax);

	if (!HPBar)
	{
		HPBar = CreateWidget<UHPBarUserWidget>(GetWorld(), HPBarClass);
		HPBar->AddToViewport();
		HPBar->AttachedActor = GetOwner();
	}

	HPBar->HPProgressBar->SetPercent(Health / HealthMax);

	if (Health < 1e-4)
	{
		auto ThisCharacter = GetOwner();
		if (ThisCharacter)
		{
			ThisCharacter->Destroy();
		}
	}
}