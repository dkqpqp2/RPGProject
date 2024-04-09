// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_PlayerController.h"
#include "UI/PA_HUDWidget.h"

APA_PlayerController::APA_PlayerController()
{
	static ConstructorHelpers::FClassFinder<UPA_HUDWidget> PAHUDWidgetRef(TEXT("/Game/Project_A/UI/WBP_PAHUD.WBP_PAHUD_C"));
	if (PAHUDWidgetRef.Class)
	{
		PA_HUDWidgetClass = PAHUDWidgetRef.Class;
	}



}

void APA_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	PA_HUDWidget = CreateWidget<UPA_HUDWidget>(this, PA_HUDWidgetClass);
	if (PA_HUDWidget)
	{
		PA_HUDWidget->AddToViewport();
	}
}





