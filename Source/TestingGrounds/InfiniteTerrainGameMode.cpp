// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"

void AInfiniteTerrainGameMode::AddToPool(class ANavMeshBoundsVolume* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Added %s to Pool"), *VolumeToAdd->GetName());
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavMeshIterator)
	{
		AddToPool(*NavMeshIterator);
		++NavMeshIterator;
	}
}
