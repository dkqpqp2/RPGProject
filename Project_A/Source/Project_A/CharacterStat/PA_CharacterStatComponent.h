// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "GameData/PA_CharacterData.h"
#include "PA_CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE(FOnMpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMpChangedDelegate, float /*CurrentMp*/);
DECLARE_MULTICAST_DELEGATE(FOnExpFullDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnExpChangedDelegate, float /*CurrentExp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FPA_CharacterData& /*BaseStat*/, const FPA_CharacterData& /*ModifierStat*/);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_A_API UPA_CharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPA_CharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FOnMpZeroDelegate OnMpZero;
	FOnMpChangedDelegate OnMpChanged;

	FOnExpFullDelegate OnExpFull;
	FOnExpChangedDelegate OnExpChanged;
	
	FOnStatChangedDelegate OnStatChanged;

	void SetLevelStat(int32 InNewLevel);
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void SetBaseStat(const FPA_CharacterData& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FPA_CharacterData& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE FPA_CharacterData GetBaseStat() const { return BaseStat; }
	FORCEINLINE FPA_CharacterData GetModifierStat() const { return ModifierStat; }
	FORCEINLINE FPA_CharacterData GetTotalStat() const { return BaseStat + ModifierStat; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetCurrentMp() { return CurrentMp; }

	float ApplyDamage(float InDamage);
	float UseSkill(float InUseSkillMp);

	FORCEINLINE float GetMaxExp() { return MaxExp; }
	FORCEINLINE float GetCurrentExp() { return CurrentExp; }
	float GetExp(float InExp);

	void LevelUp();

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxMp = 100.0f;

protected:
	void SetHp(float NewHp);
	void SetMp(float NewMp);
	void SetExp(float NewExp);             

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentMp;

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FPA_CharacterData BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FPA_CharacterData ModifierStat;
		
};
