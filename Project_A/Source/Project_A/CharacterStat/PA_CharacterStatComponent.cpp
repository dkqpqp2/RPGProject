// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterStatComponent.h"
#include "GameData/PA_GameSingleton.h"

// Sets default values for this component's properties
UPA_CharacterStatComponent::UPA_CharacterStatComponent()
{
	CurrentLevel = 1;
	MaxExp = 100.0f;
	CurrentExp = 0.0f;

	bWantsInitializeComponent = true;

}

void UPA_CharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	CurrentExp = 0.0f;
	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UPA_CharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UPA_GameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(UPA_GameSingleton::Get().GetCharacterData(CurrentLevel));
	check(BaseStat.MaxHp > 0.0f);
}

float UPA_CharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}


float UPA_CharacterStatComponent::GetExp(float InExp)
{
	const float PrevExp = CurrentExp;
	const float ActualExp = FMath::Clamp<float>(InExp, 0, InExp);
	SetExp(PrevExp + ActualExp);
	if (CurrentExp >= MaxExp)
	{
		OnExpFull.Broadcast();
	}

	return ActualExp;
}

void UPA_CharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}

void UPA_CharacterStatComponent::SetExp(float NewExp)
{
	CurrentExp = FMath::Clamp<float>(NewExp, 0.0f, MaxExp);

	OnExpChanged.Broadcast(CurrentExp);
}




