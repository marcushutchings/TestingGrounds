// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Public/PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	auto AIOwner = OwnerComp.GetAIOwner();
	if (!AIOwner) return EBTNodeResult::Failed;
	
	auto Pawn = AIOwner->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;
	
	auto PatrolGuard = Cast<APatrollingGuard>(Pawn);
	if (!PatrolGuard) return EBTNodeResult::Failed;
	
	auto PatrolPoints = PatrolGuard->GetPatrolPoints();
	if (PatrolPoints.Num() <= Index) return EBTNodeResult::Failed;
	
	auto NextWaypoint = PatrolPoints[Index];
	if (!NextWaypoint) return EBTNodeResult::Failed;

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, NextWaypoint);
	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	//UE_LOG(LogTemp, Warning, TEXT("ChooseNextWaypoint %d"), PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}
