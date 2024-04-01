// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackHitCheck.h"
#include "Interface/PA_AnimationAttackInterface.h"

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IPA_AnimationAttackInterface* AttackPawn = Cast<IPA_AnimationAttackInterface>(MeshComp->GetOwner());
		if(AttackPawn)
		{
			AttackPawn->AttackHitCheck();
		}
	}
}
