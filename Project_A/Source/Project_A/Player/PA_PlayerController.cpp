// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_PlayerController.h"

APA_PlayerController::APA_PlayerController()
{
	bShowMouseCursor = true;
}

void APA_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}





