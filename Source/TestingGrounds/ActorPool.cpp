// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UActorPool::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UActorPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor * UActorPool::Checkout()
{
	if (PoolOfActors.Num() == 0) return nullptr;

	return PoolOfActors.Pop(false);
}

void UActorPool::Return(AActor * ActorToReturn)
{
	Add(ActorToReturn);
}

void UActorPool::Add(AActor * ActorToAdd)
{
	if (ActorToAdd)
		if (!PoolOfActors.Contains(ActorToAdd))
			PoolOfActors.Add(ActorToAdd);
}

