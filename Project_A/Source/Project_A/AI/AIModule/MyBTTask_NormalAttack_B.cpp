// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_NormalAttack_B.h"
#include "../PA_AIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"

UMyBTTask_NormalAttack_B::UMyBTTask_NormalAttack_B()
{
	NodeName = TEXT("NormalAttack_B");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMyBTTask_NormalAttack_B::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

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

		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::AttackRight);


	return EBTNodeResult::InProgress;
}

void UMyBTTask_NormalAttack_B::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return;
	}

	if (Pawn->IsAttackRightEnd())
	{
		Pawn->SetAttackRightEnd(false);
		FVector AILocation = Pawn->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();

		FVector Dir = TargetLocation - AILocation;
		Dir.Z = 0.0;

		AILocation.Z -= Pawn->GetHalfHeight();

		UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

		if (IsValid(TargetCapsule))
		{
			TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
		}

		float Distance = FVector::Distance(AILocation, TargetLocation);

		if (Distance > 200.f)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

			Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
		}
		else
		{
			FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
			Rot.Pitch = 0.0;
			Rot.Roll = 0.0;

			Pawn->SetActorRotation(Rot);
		}

	}
}
