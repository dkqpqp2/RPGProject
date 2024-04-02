// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_AIController.h"
#include "PA_AI.h"

APA_AIController::APA_AIController()
{

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_A/Blueprint/AI/BT_Default.BT_Default'"));
	if (BehaviorTreeRef.Object)
	{
		BehaviorTree = BehaviorTreeRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/Project_A/Blueprint/AI/BB_Default.BB_Default'"));
	if (BlackboardDataRef.Object)
	{
		BlackboardData = BlackboardDataRef.Object;
	}
}

void APA_AIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BlackboardData, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());
		bool RunResult = RunBehaviorTree(BehaviorTree);
		ensure(RunResult);
	}
}

void APA_AIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void APA_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 블랙보드가 있을 경우
	if (BlackboardData)
	{
		UBlackboardComponent* BlackboardRef = Blackboard;
		if (UseBlackboard(BlackboardData, BlackboardRef))
		{
			RunBehaviorTree(BehaviorTree);
		}
	}

}

void APA_AIController::OnUnPossess()
{
	Super::OnUnPossess();


}
