// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyCharacter.h"

// Sets default values
ABasicEnemyCharacter::ABasicEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void ABasicEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();	

	HealthComponent->HPBarClass = HPBarClass;
}

// Called every frame
void ABasicEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ABasicEnemyCharacter::CauseDamage(float Value)
{
	if (HealthComponent)
	{
		HealthComponent->ApplyHealthChange(-Value);
	}
}

