// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "PA_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	EPlayerType SelectPlayerType;

public:
	void SetPlayerType(EPlayerType Type)
	{
		SelectPlayerType = Type;
	}

	EPlayerType GetPlayerType()
	{
		return SelectPlayerType;
	}

};
