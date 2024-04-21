// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_GameMode.h"
#include "Player/PA_PlayerController.h"
#include "../Character/PA_CharacterState.h"
#include "../Character/PA_ArcherCharacter.h"
#include "../Character/PA_KnightCharacter.h"
#include "../PA_GameInstance.h"

APA_GameMode::APA_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPlayerRef(TEXT("/Game/Project_A/Blueprint/BP_PA_CharacterPlayer.BP_PA_CharacterPlayer_C"));
	if (DefaultPlayerRef.Class)
	{
		DefaultPawnClass = DefaultPlayerRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APA_PlayerController> PlayerControllerClassRef(TEXT("/Game/Project_A/Blueprint/PA_PlayerController.PA_PlayerController_C")); 
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	PlayerStateClass = APA_CharacterState::StaticClass();
}

void APA_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EPlayerType PlayerType = GetWorld()->GetGameInstance<UPA_GameInstance>()->GetPlayerType();

	switch (PlayerType)
	{
	case EPlayerType::Knight:

		break;
	case EPlayerType::Archer:

		break;
	}
}

APlayerController* APA_GameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);



	return result;
}
