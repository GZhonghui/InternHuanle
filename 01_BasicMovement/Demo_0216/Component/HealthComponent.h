// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Components/ProgressBar.h"

#include "../UI/EnemyHealthWidget.h"

#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAttributeChange, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_0216_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	float Health;
	float HealthMax;

public:
	class UEnemyHealthWidget* HPBar;
	class TSubclassOf<UEnemyHealthWidget> HPBarClass;

public:
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(APawn* someActor, float Value);
};
