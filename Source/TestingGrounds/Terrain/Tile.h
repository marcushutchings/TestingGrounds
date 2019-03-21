// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()

	bool CanSpawnAtLocation(FVector Location, float Radius);

	FVector ChooseSpawnLocation();

	bool TryFindSafeSpawnLocation(FVector& OutLocation, float SafeRadius);

	void SpawnActor(TSubclassOf<AActor> ToSpawn, FVector Location);

public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PlaceTerrain(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn, float SafeRadius = 300.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
