// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "PA_MonsterWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_MonsterWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
protected:
	virtual void InitWidget() override;
};
