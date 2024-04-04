// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SpawnSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UBTTask_SpawnSkill : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SpawnSkill();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
