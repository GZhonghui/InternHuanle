// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../UI/HPBarUserWidget.h"

#include "../Component/HealthComponent.h"

#include "BasicEnemyCharacter.generated.h"

UCLASS()
class FINAL_API ABasicEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	class UHealthComponent* HealthComponent;

public:
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UHPBarUserWidget> HPBarClass;
	class UHPBarUserWidget* HPBar;

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(float Value);
};
