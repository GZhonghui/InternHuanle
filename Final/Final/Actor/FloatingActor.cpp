// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemID = 1;
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));

	NowLocation = 0;
	FloatingUP = true;
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float FloatingSpeed = 40;
	const float FloatingLimit = 20;

	if (Mesh)
	{
		auto NowMeshLocation = Mesh->GetRelativeLocation();
		NowMeshLocation.Z += DeltaTime * FloatingSpeed * (FloatingUP ? 1 : -1);
		Mesh->SetRelativeLocation(NowMeshLocation);
		if (NowMeshLocation.Z > FloatingLimit) FloatingUP = false;
		if (NowMeshLocation.Z < -FloatingLimit) FloatingUP = true;

		Mesh->AddRelativeRotation(FRotator(0, DeltaTime * 30, 0));
	}
}

