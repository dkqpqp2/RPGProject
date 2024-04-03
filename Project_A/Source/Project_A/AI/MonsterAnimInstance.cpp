// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterPawn.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = EMonsterAnimType::Idle;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());

	//float Random = FMath::RandRange(0.0f, 5.0f);

	Pawn->NormalAttack();
	//if (Random < 1.0f)
	//{
	//	Pawn->NormalAttack();
	//}
	//else
	//{
	//	Pawn->NormalAttack_B();
	//}

}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());
	Pawn->SetAttackEnd(true);
}

void UMonsterAnimInstance::AnimNotify_AttackRight()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());
	Pawn->NormalAttack_B();

}

void UMonsterAnimInstance::AnimNotify_AttackRightEnd()
{
	AMonsterPawn* Pawn = Cast<AMonsterPawn>(TryGetPawnOwner());
	Pawn->SetAttackRightEnd(true);
}
