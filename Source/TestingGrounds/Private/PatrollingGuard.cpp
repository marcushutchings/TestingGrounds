// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrollingGuard.h"
#include "Public/PatrollingGuard.h"

const TArray<AActor*> APatrollingGuard::GetPatrolPoints() const
{
	return PatrolPoints;
}
