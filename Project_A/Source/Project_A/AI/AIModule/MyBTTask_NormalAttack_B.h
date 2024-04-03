// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_NormalAttack_B.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UMyBTTask_NormalAttack_B : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMyBTTask_NormalAttack_B();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
