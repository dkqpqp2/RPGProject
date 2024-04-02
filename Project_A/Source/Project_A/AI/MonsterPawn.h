// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "MonsterPawn.generated.h"


UCLASS()
class PROJECT_A_API AMonsterPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	AMonsterPawn();

public:
	virtual void ChangeAIAnimType(uint8 AnimType) override;

protected:
	class UMonsterAnimInstance* MonsterAnimInst;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();
};
