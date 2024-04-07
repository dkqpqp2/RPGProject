// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "PA_MonsterWidget.h"
#include "PA_MonsterHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_MonsterHpBarWidget : public UPA_MonsterWidget
{
	GENERATED_BODY()

public:
	UPA_MonsterHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
	
};
