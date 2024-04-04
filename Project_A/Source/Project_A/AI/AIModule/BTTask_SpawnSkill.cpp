// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnSkill.h"
#include "../PA_AIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"

UBTTask_SpawnSkill::UBTTask_SpawnSkill()
{
	NodeName = TEXT("SpawnSkill");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_SpawnSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = CastChecked<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = CastChecked<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		return EBTNodeResult::Failed;
	}







	return EBTNodeResult::Type();
}

void UBTTask_SpawnSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
