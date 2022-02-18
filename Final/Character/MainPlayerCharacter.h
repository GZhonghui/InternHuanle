// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "Misc/DateTime.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainPlayerCharacter.generated.h"

UCLASS()
class FINAL_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TArray<class UAnimMontage*> AttackAnims;

public:
	UPROPERTY(BlueprintReadWrite)
	bool Attacking;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Attack();

	FDateTime LastAttack;

	int WhichAttackState;

	const double AttackNumberTimeMax = 5000;

public:
	UFUNCTION(BlueprintCallable)
	void AttackPoint();

public:
	int AttackNumberValue;
	float AttackTimeValue;

public:
	UFUNCTION(BlueprintCallable)
	float GetSpeed();
};
