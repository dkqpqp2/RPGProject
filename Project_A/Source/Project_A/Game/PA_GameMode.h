// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "PA_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API APA_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APA_GameMode();


public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
};
