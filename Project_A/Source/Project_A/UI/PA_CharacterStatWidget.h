// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PA_CharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_CharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(const FPA_CharacterData& BaseStat, const FPA_CharacterData& ModifierStat);
	

private:
	UPROPERTY()
	TMap<FName, class UTextBlock*> BaseLookup;

	UPROPERTY()
	TMap<FName, class UTextBlock*> ModifierLookup;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TxtMaxHpBase;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtMaxHpModifier;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAttackDamageBase;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAttackDamageModifier;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAttackRangeBase;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAttackRangeModifier;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAttackSpeedBase;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtAttackSpeedModifier;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtMovementSpeedBase;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TxtMovementSpeedModifier;
};
