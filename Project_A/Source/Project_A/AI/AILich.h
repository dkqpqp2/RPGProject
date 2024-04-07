// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterPawn.h"
#include "AILich.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API AAILich : public AMonsterPawn
{
	GENERATED_BODY()
public:
	AAILich();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//TSubclassOf<AAILichProjectile> AILichProjectileClass;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NormalAttack();
	virtual void NormalAttack_B();
	//virtual void SkillA();


	void SetDead() override;

};
