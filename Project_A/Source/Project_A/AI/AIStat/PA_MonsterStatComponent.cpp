// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_MonsterStatComponent.h"

// Sets default values for this component's properties
UPA_MonsterStatComponent::UPA_MonsterStatComponent()
{
	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}


// Called when the game starts
void UPA_MonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
}

float UPA_MonsterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float AutaulDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - AutaulDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
		bDead = true;
	}

	return AutaulDamage;
}

void UPA_MonsterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}


