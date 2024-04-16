// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PA_MonsterStatComponent.h"
#include "AIMonsterStatData.h"
#include "MonsterState.generated.h"



UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PROJECT_A_API UMonsterState : public UPA_MonsterStatComponent
{
	GENERATED_BODY()

public:
	UMonsterState();

public:
	UPROPERTY(EditAnywhere)
	EMonsterType Type;

	UPROPERTY(EditAnywhere)
	FString MonsterName;

	UPROPERTY(EditAnywhere)
	float Level;

	UPROPERTY(EditAnywhere)
	float MaxHp;

	UPROPERTY(EditAnywhere)
	float AttackDamage;

	UPROPERTY(EditAnywhere)
	float MonsterArmor;

	UPROPERTY(EditAnywhere)
	float AttackSpeed;

	UPROPERTY(EditAnywhere)
	float AttackDistance;

	UPROPERTY(EditAnywhere)
	float MonsterExp;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
