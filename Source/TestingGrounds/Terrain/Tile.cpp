// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

#include "DrawDebugHelpers.h"

#define MAX_ATTEMPTS 50

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HitFound = GetWorld()->SweepSingleByChannel
		( HitResult
		, GlobalLocation
		, GlobalLocation
		, FQuat::Identity
		, ECollisionChannel::ECC_GameTraceChannel2
		, FCollisionShape::MakeSphere(Radius)
		);
	
	FColor DebugColour = HitFound ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, DebugColour, true, 100.f);
	
	return !HitFound;
}

FVector ATile::ChooseSpawnLocation()
{
	FVector PlacementMinBoundary(0.f, -1950.f, 0.f);
	FVector PlacementMaxBoundary(4000.f, 1950.f, 0.f);
	FBox PlacementZone(PlacementMinBoundary, PlacementMaxBoundary);

	return FMath::RandPointInBox(PlacementZone);
}

bool ATile::TryFindSafeSpawnLocation(FVector& OutLocation, float SafeRadius)
{
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector SpawnPoint = ChooseSpawnLocation();
		if (CanSpawnAtLocation(SpawnPoint, SafeRadius))
		{
			OutLocation = SpawnPoint;
			return true;
		}
	}
	return false;
}

void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, FVector Location)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
}

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

void ATile::PlaceTerrain(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn, float SafeRadius)
{
	size_t NumberToSpawn = FMath::RandRange(MinToSpawn, MaxToSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		if (TryFindSafeSpawnLocation(SpawnPoint, SafeRadius))
			SpawnActor(ToSpawn, SpawnPoint);
		else
			UE_LOG(LogTemp, Error, TEXT("Failed to fail safe spawn for %s, number %d"), *ToSpawn->GetName(), i+1);
	}
}
