// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class UActorPool;

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoundsPool")
		UActorPool* PoolOfNavMeshBoundsVolume;

	UPROPERTY(VisibleAnywhere, Category = "Scoring")
		int32 PlayerScore = 0;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Scoring")
		int32 GetPlayerScore() const;

	UFUNCTION(BlueprintCallable, Category = "Scoring")
		void NewTileConquered();

	UFUNCTION(BlueprintCallable, Category = "BoundsPool")
		void PopulateBoundsVolumePool();
};
