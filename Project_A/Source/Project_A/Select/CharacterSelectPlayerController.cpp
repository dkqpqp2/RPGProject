// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectPlayerController.h"
#include "Character/PA_CharacterPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SelectPlayer.h"

ACharacterSelectPlayerController::ACharacterSelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;

	HitActor = nullptr;
}

void ACharacterSelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const USelectInputDataConfig* SelectInputDataConfig = GetDefault<USelectInputDataConfig>();
	Subsystem->AddMappingContext(SelectInputDataConfig->DefaultSelectContext, 0);

	FInputModeGameAndUI InputMode;

	SetInputMode(InputMode);



}

void ACharacterSelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	const USelectInputDataConfig* SelectInputDataConfig = GetDefault<USelectInputDataConfig>();
	EnhancedInputComponent->BindAction(SelectInputDataConfig->Select, ETriggerEvent::Completed, this, &ACharacterSelectPlayerController::OnSelect);
	

}

void ACharacterSelectPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult result;
	bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false,
		result);

	if(Hit)
	{
		HitActor = result.GetActor();
	}
	else
	{
		HitActor = nullptr;
	}


}

void ACharacterSelectPlayerController::OnSelect(const FInputActionValue& Value)
{
	if (IsValid(HitActor))
	{
		ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(HitActor);
		if (IsValid(SelectPlayer))
		{
			SelectPlayer->SetSelect(true);
		}
	}
}
