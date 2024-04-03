// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	AttackLeft,
	AttackRight,
	Spawn,
	Hit,
	Death,
	Skill
};
/**
 * 
 */
UCLASS()
class PROJECT_A_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterAnimType mAnimType;


public:
	void ChangeAnimType(EMonsterAnimType Type)
	{
		mAnimType = Type;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds); 

public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_AttackRight();

	UFUNCTION()
	void AnimNotify_AttackRightEnd();
};
