// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPatrol.h"

// Sets default values for this component's properties
UCharacterPatrol::UCharacterPatrol()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterPatrol::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterPatrol::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const TArray<AActor*> UCharacterPatrol::GetPatrolPoints() const
{
	return PatrolPoints;
}