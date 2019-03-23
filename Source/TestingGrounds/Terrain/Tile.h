// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float YawRotation;
	float Scale;
};

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()

	bool CanSpawnAtLocation(FVector Location, float Radius);

	FVector ChooseSpawnLocation();

	bool TryFindSafeSpawnLocation(FVector& OutLocation, float SafeRadius);

	void SpawnActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	void PositionNavMeshBoundsVolume();

public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceTerrain(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn, float MinScale = 1.f, float MaxScale = 1.f, float SafeRadius = 300.f);

	TArray<FSpawnPosition> GenerateSpawnPositions(int32 MinToSpawn, int32 MaxToSpawn, float MinScale, float MaxScale, float SafeRadius, TSubclassOf<AActor> &ToSpawn);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetNavMeshVolumePool(class UActorPool* PoolToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		FVector PlacementMinBoundary;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		FVector PlacementMaxBoundary;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		FVector NavMeshBoundryVolumeDisplacement;

private:

	UPROPERTY()
		class UActorPool* NavMeshVolumePool;

	UPROPERTY()
		AActor* NavMeshBoundsVolume = nullptr;
};
