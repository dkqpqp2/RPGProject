// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PA_UserWidget.h"
#include "MpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UMpBarWidget : public UPA_UserWidget
{
	GENERATED_BODY()
public:
	UMpBarWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxMp(float NewMaxMp) { MaxMp = NewMaxMp; }
	void UpdateMpBar(float NewCurrentMp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> MpProgressBar;

	UPROPERTY()
	float MaxMp;
};
