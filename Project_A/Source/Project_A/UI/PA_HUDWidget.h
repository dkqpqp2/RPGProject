// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "GameData/PA_CharacterData.h"
#include "PA_HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPA_HUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateStat(const FPA_CharacterData& BaseStat, const FPA_CharacterData& ModifierStat);
	void UpdateHpBar(float NewCurrentHp);
	void UpdateMpBar(float NewCurrentMp);
	void UpdateExpBar(float NewCurrentExp);

protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY()
	TObjectPtr<class UPA_HpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UMpBarWidget> MpBar;

	UPROPERTY()
	TObjectPtr<class UPA_CharacterStatWidget> CharacterStat;

	UPROPERTY()
	TObjectPtr<class UPA_ExpBarWidget> ExpBar;
};
