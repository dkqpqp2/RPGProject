// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PA_UserWidget.h"
#include "PA_ExpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_ExpBarWidget : public UPA_UserWidget
{
	GENERATED_BODY()

public:
	UPA_ExpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxExp(float NewMaxExp) { MaxExp = NewMaxExp; }
	void UpdateExpBar(float NewCurrentExp);
	
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> ExpProgressBar;

	UPROPERTY()
	float MaxExp;
};
