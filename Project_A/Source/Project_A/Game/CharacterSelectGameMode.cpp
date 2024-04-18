// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"
#include "Select/CharacterSelectPlayerController.h"
#include "Select/CharacterSelectPawn.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{

	PlayerControllerClass = ACharacterSelectPlayerController::StaticClass();
	//DefaultPawnClass = ACharacterSelectPawn::StaticClass();

}
