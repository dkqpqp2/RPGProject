// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SelectAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API USelectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USelectAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelect;

public:
	void SetSelect(bool InSelect)
	{
		IsSelect = InSelect;
	}

public:
	UFUNCTION()
	void AnimNotify_TransitionSelect();
};
