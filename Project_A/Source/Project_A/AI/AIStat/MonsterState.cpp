// Fill out your copyright notice in the Description page of Project Settings.
#include "MonsterState.h"
#include "AI/MonsterPawn.h"

UMonsterState::UMonsterState()
{
	CurrentHp = MaxHp;
}

void UMonsterState::BeginPlay()
{
	Super::BeginPlay();

	const FAIMonsterStatData* Data = AMonsterPawn::FindMonsterData(DataTableRowName);

	if (Data)
	{
		Type = Data->Type;
		MonsterName = Data->MonsterName;
		Level = Data->Level;
		CurrentHp = Data->MaxHp;
		MaxHp = Data->MaxHp;
		AttackDamage = Data->AttackDamage;
		MonsterArmor = Data->MonsterArmor;
		AttackSpeed = Data->AttackSpeed;
		MovementSpeed = Data->MovementSpeed;
		AttackDistance = Data->AttackDistance;
		InteractionDistance = Data->TraceDistance;
		MonsterExp = Data->MonsterExp;
	}
	SetHp(MaxHp);
}


