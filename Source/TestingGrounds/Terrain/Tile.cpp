// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "InfiniteTerrainGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "NavigationSystem.h"

#include "DrawDebugHelpers.h"

#define MAX_ATTEMPTS 20

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
	
	//FColor DebugColour = HitFound ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, DebugColour, true, 100.f);
	
	return !HitFound;
}

FVector ATile::ChooseSpawnLocation()
{
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

void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Spawned->SetActorRotation(FRotator(0.f, SpawnPosition.YawRotation, 0.f));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::SpawnAIPawn(TSubclassOf<APawn> ToSpawn, const FSpawnPosition & SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Spawned->SetActorRotation(FRotator(0.f, SpawnPosition.YawRotation, 0.f));
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("GuardBots"));
}

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlacementMinBoundary = FVector(0.f, -1950.f, 0.f);
	PlacementMaxBoundary = FVector(4000.f, 1950.f, 0.f);
	NavMeshBoundryVolumeDisplacement = FVector(2000.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (NavMeshVolumePool)
		NavMeshVolumePool->Return(NavMeshBoundsVolume);
	UE_LOG(LogTemp, Error, TEXT("End Play Called on me %s."), *GetName());
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceTerrain(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn, float MinScale, float MaxScale, float SafeRadius)
{
	TArray<FSpawnPosition> SpawnPositions = GenerateSpawnPositions(MinToSpawn, MaxToSpawn, MinScale, MaxScale, SafeRadius);

	for (auto SpawnPosition : SpawnPositions)
	{
		SpawnActor(ToSpawn, SpawnPosition);
	}
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn, float SafeRadius)
{
	TArray<FSpawnPosition> SpawnPositions = GenerateSpawnPositions(MinToSpawn, MaxToSpawn, 1.f, 1.f, SafeRadius);

	for (auto SpawnPosition : SpawnPositions)
	{
		SpawnAIPawn(ToSpawn, SpawnPosition);
	}
}

TArray<FSpawnPosition> ATile::GenerateSpawnPositions(int32 MinToSpawn, int32 MaxToSpawn, float MinScale, float MaxScale, float SafeRadius)
{
	TArray<FSpawnPosition> SpawnPositions;
	size_t NumberToSpawn = FMath::RandRange(MinToSpawn, MaxToSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);

		if (TryFindSafeSpawnLocation(SpawnPosition.Location, SafeRadius*SpawnPosition.Scale))
		{
			SpawnPosition.YawRotation = FMath::RandRange(-180.f, 180.f);
			SpawnPositions.Add(SpawnPosition);
		}
	}
	return SpawnPositions;
}

void ATile::SetNavMeshVolumePool(UActorPool * PoolToSet)
{
	NavMeshVolumePool = PoolToSet;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	if (NavMeshVolumePool)
	{
		NavMeshBoundsVolume = NavMeshVolumePool->Checkout();
		if (NavMeshBoundsVolume)
		{
			NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavMeshBoundryVolumeDisplacement);
			FNavigationSystem::Build(*GetWorld());
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Not enough Nav Mesh Bounds Volumes in the Pool."));
	}
}
