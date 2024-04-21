// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterPawn.h"
#include "AIGoblin.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API AAIGoblin : public AMonsterPawn
{
	GENERATED_BODY()

public:
	AAIGoblin();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NormalAttack();
	virtual void NormalAttack_B();

	UFUNCTION(BlueprintCallable)
	void SetDead() override;

};
