// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "SelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API USelectWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY()
	UButton* StartButton;

protected:
	virtual void NativeConstruct() override;

public:
	void SetStartButtonEnable(bool InEnable);
	
	UFUNCTION()
	void StartButtonClick();
};
