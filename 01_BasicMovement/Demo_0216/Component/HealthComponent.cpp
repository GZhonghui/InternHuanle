// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Health = HealthMax = 100;

	static ConstructorHelpers::FClassFinder<UEnemyHealthWidget> WidgetBPClass(TEXT("/Game/0_Main/UI/UI_EnemyBar"));
	HPBarClass = WidgetBPClass.Class;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthComponent::ApplyHealthChange(APawn* someActor, float Value)
{
	if (!HPBar)
	{
		HPBar = CreateWidget<UEnemyHealthWidget>(GetWorld(), HPBarClass);
		HPBar->AttachedActor = GetOwner();
		HPBar->AddToViewport();
	}

	float oldHealth = Health;
	Health = FMath::Clamp(Health + Value, 0.0f, HealthMax);

	if (Health < 1e-4)
	{
		GetOwner()->Destroy();
	}

	HPBar->HPProgressBar->SetPercent(Health / HealthMax);

	return FMath::Abs(Value) > 1e-4;
}