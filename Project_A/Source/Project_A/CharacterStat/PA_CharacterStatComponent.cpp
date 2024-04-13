// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterStatComponent.h"
#include "GameData/PA_GameSingleton.h"

// Sets default values for this component's properties
UPA_CharacterStatComponent::UPA_CharacterStatComponent()
{
	CurrentLevel = 1;
	CurrentExp = 0.0f;
	bWantsInitializeComponent = true;

}

void UPA_CharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	SetHp(BaseStat.MaxHp);
	SetMp(100.0f);
	SetExp(CurrentExp);
}

void UPA_CharacterStatComponent::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UPA_GameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(UPA_GameSingleton::Get().GetCharacterData(CurrentLevel));
	check(BaseStat.MaxHp > 0.0f);
}

void UPA_CharacterStatComponent::SetBaseStat(const FPA_CharacterData& InBaseStat)
{
	BaseStat = InBaseStat; 
	OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
}

void UPA_CharacterStatComponent::SetModifierStat(const FPA_CharacterData& InModifierStat)
{
	ModifierStat = InModifierStat;
	OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
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

float UPA_CharacterStatComponent::UseSkill(float InUseSkillMp)
{
	const float PrevMp = CurrentMp;
	const float ActualSkillMp = FMath::Clamp<float>(InUseSkillMp, 0, InUseSkillMp);

	SetMp(PrevMp - ActualSkillMp);
	if (CurrentMp <= KINDA_SMALL_NUMBER)
	{
		OnMpZero.Broadcast();
	}

	return ActualSkillMp;
}

float UPA_CharacterStatComponent::GetExp(float InExp)
{
	const float PrevExp = CurrentExp;
	const float ActualExp = FMath::Clamp<float>(InExp, 0, InExp);
	SetExp(PrevExp + ActualExp);
	if (CurrentExp >= BaseStat.MaxExp)
	{
		OnExpFull.Broadcast();
		LevelUp();
	}

	return ActualExp;
}

void UPA_CharacterStatComponent::LevelUp()
{
	
	if (CurrentExp >= BaseStat.MaxExp)
	{
		float PlusCurrentExp = CurrentExp - BaseStat.MaxExp;
		float NextLevel = ++CurrentLevel;
		SetLevelStat(NextLevel);
		SetExp(PlusCurrentExp);
	}

}

void UPA_CharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, BaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}

void UPA_CharacterStatComponent::SetMp(float NewMp)
{
	CurrentMp = FMath::Clamp<float>(NewMp, 0.0f, MaxMp);

	OnMpChanged.Broadcast(CurrentMp);
}

void UPA_CharacterStatComponent::SetExp(float NewExp)
{
	CurrentExp = NewExp;

	OnExpChanged.Broadcast(CurrentExp);
}




