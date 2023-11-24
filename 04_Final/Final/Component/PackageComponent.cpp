// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageComponent.h"

// Sets default values for this component's properties
UPackageComponent::UPackageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPackageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	for (int i = 1; i <= MaxStack; ++i)
	{
		StackID.Emplace(i, 0);
		StackNumber.Emplace(i, 0);
	}
	
}


// Called every frame
void UPackageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPackageComponent::AddItem(int ItemID, int Count)
{
	int FirstEmpty = 0;

	for (int i = 1; i <= MaxStack; ++i)
	{
		if (StackID[i] == ItemID && StackNumber[i])
		{
			StackNumber[i] += Count;
			return true;
		}

		if (!FirstEmpty && StackNumber[i] == 0)
		{
			FirstEmpty = i;
		}
	}

	if (FirstEmpty)
	{
		StackID[FirstEmpty] = ItemID;
		StackNumber[FirstEmpty] = Count;

		return true;
	}

	return false;
}
