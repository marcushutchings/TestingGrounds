// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	PlaceTerrain();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceTerrain()
{
	FVector PlacementMinBoundary(0.f, -1950.f, 0.f);
	FVector PlacementMaxBoundary(4000.f, 1950.f, 0.f);
	FBox PlacementZone(PlacementMinBoundary, PlacementMaxBoundary);

	for (size_t i = 0; i < 20; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(PlacementZone);
		UE_LOG(LogTemp, Warning, TEXT("Spawn Point %s chosen"), *SpawnPoint.ToString())
	}
}

