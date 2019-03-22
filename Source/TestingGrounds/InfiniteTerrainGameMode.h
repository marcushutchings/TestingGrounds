// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

public:
	UFUNCTION(BlueprintCallable, Category = "BoundsPool")
		void PopulateBoundsVolumePool();
};
