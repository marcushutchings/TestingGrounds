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

// This is an interesting idea, but is meesy in Blueprint
USTRUCT(BlueprintType)
struct FRandomSpawnParameters
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	int32 MinToSpawn = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	int32 MaxToSpawn = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	float MinScale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	float MaxScale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	float SafeRadius = 100.f;
};

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()

	bool CanSpawnAtLocation(FVector Location, float Radius);

	FVector ChooseSpawnLocation();

	bool TryFindSafeSpawnLocation(FVector& OutLocation, float SafeRadius);

	void SpawnActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	void SpawnAIPawn(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition);

	void PositionNavMeshBoundsVolume();

public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceTerrain(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn = 1, int32 MaxToSpawn = 1, float MinScale = 1.f, float MaxScale = 1.f, float SafeRadius = 300.f);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinToSpawn = 1, int32 MaxToSpawn = 1, float SafeRadius = 100.f);

	TArray<FSpawnPosition> GenerateSpawnPositions(int32 MinToSpawn, int32 MaxToSpawn, float MinScale, float MaxScale, float SafeRadius);

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
