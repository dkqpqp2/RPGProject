// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "PA_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API APA_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APA_AIController();

	void RunAI();
	void StopAI();

protected:
	UBehaviorTree* BehaviorTree;
	UBlackboardData* BlackboardData;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};
