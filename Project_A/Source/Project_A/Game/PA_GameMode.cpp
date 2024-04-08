// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_GameMode.h"
#include "Player/PA_PlayerController.h"
#include "../Character/PA_CharacterState.h"

APA_GameMode::APA_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPlayerRef(TEXT("/Game/Project_A/Blueprint/BP_PA_CharacterPlayer.BP_PA_CharacterPlayer_C"));
	if (DefaultPlayerRef.Class)
	{
		DefaultPawnClass = DefaultPlayerRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APA_PlayerController> PlayerControllerClassRef(TEXT("/Script/Project_A.PA_PlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	PlayerStateClass = APA_CharacterState::StaticClass();
}
