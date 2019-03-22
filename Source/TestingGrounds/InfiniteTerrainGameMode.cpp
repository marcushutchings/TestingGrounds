// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "ActorPool.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"

void AInfiniteTerrainGameMode::AddToPool(class ANavMeshBoundsVolume* VolumeToAdd)
{
	//PoolOfNavMeshBoundsVolume->Add(VolumeToAdd);
	UE_LOG(LogTemp, Warning, TEXT("Added %s to Pool"), *VolumeToAdd->GetName());
}

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	PoolOfNavMeshBoundsVolume = CreateDefaultSubobject<UActorPool>(TEXT("Nav Mesh Volume Pool"));
	//UE_LOG(LogTemp, Warning, TEXT("Added %s to Pool %s DOnE!!!!"), *PoolOfNavMeshBoundsVolume->GetName(), *GetName());
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

