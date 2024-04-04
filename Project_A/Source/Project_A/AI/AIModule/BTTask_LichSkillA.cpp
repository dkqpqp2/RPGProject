// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LichSkillA.h"
#include "../PA_AIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"

UBTTask_LichSkillA::UBTTask_LichSkillA()
{
}

EBTNodeResult::Type UBTTask_LichSkillA::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{

		Controller->StopMovement();

		Pawn->ChangeAIAnimType(static_cast<uint8>(EMonsterAnimType::Idle));

		return EBTNodeResult::Failed;
	}

	Pawn->ChangeAIAnimType(static_cast<uint8>(EMonsterAnimType::Skill));

	return EBTNodeResult::InProgress;
}

void UBTTask_LichSkillA::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
