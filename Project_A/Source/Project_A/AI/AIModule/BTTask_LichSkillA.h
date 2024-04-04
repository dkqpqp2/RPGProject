// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LichSkillA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UBTTask_LichSkillA : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LichSkillA();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
