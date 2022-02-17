// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "Animation/AnimMontage.h"

#include "Camera/CameraComponent.h"

#include "Component/HealthComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "HeroCharacter.generated.h"

UCLASS()
class DEMO_0216_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class USpringArmComponent* SpringArm;

	class UCameraComponent* Camera;

public:
	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	bool isRunning();

	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* AttackAnim;

	void Attack();
};
