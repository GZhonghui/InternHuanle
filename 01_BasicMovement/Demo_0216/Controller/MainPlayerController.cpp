// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Change", IE_Pressed, this, &AMainPlayerController::Change);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CurrentHero = 0;
}

void AMainPlayerController::Change()
{
	auto Now = GetPawn();
	auto Transform = Now->GetTransform();

	auto CameraTransform = Cast<AHeroCharacter>(Now)->Camera->GetComponentTransform();

	// static ConstructorHelpers::FClassFinder<AHeroCharacter> HeroClass(TEXT("/Game/0_Main/Character/BP_HeroCharacter_01"));

	
	// auto New = GetWorld()->SpawnActor(HeroClass.Class, &Transform);

	CurrentHero = 1 - CurrentHero;
	
	auto New = GetWorld()->SpawnActor(newHeroClass[CurrentHero], &Transform);
	// Cast<AHeroCharacter>(New)->Camera->SetWorldTransform(CameraTransform);

	Possess(Cast<ACharacter>(New));
	Now->Destroy();
}