// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

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
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceTerrain(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn)
{
	FVector PlacementMinBoundary(0.f, -1950.f, 0.f);
	FVector PlacementMaxBoundary(4000.f, 1950.f, 0.f);

	//PlacementMinBoundary += GetActorLocation();
	//PlacementMaxBoundary += GetActorLocation();

	FBox PlacementZone(PlacementMinBoundary, PlacementMaxBoundary);
	size_t NumberToSpawn = FMath::RandRange(MinToSpawn, MaxToSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(PlacementZone);
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	}
}

