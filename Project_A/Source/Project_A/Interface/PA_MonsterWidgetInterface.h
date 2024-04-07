// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/Interface.h"
#include "PA_MonsterWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPA_MonsterWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_A_API IPA_MonsterWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupMonsterWidget(class UPA_MonsterWidget* InMonsterWidget) = 0;
};
