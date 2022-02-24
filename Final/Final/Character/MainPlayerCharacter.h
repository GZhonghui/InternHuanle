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
#include "Components/CapsuleComponent.h"

#include "../Component/PackageComponent.h"
#include "../Component/ArmsComponent.h"

#include "../Actor/FloatingActor.h"

#include "BasicEnemyCharacter.h"

#include "MainPlayerCharacter.generated.h"

DECLARE_DELEGATE_TwoParams(FLogAMessage, const FString&, float);

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

public:
	FLogAMessage LogMyMessage;

public:
	UPROPERTY(BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadWrite)
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

public:
	class UPackageComponent* Package;

public:
	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
