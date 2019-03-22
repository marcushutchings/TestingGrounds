// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<AActor*> PoolOfActors;

public:	
	// Sets default values for this component's properties
	UActorPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
		AActor* Checkout();

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void Return(AActor* ActorToReturn);

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void Add(AActor* ActorToAdd);
};
