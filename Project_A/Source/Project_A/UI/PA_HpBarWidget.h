// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PA_UserWidget.h"
#include "PA_HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_HpBarWidget : public UPA_UserWidget
{
	GENERATED_BODY()
	
public:
	UPA_HpBarWidget(const FObjectInitializer& ObjectInitializer);

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
