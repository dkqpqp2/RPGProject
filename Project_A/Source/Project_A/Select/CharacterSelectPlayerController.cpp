// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectPlayerController.h"
#include "Character/PA_CharacterPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SelectPlayer.h"
#include "UI/SelectWidget.h"
#include "../PA_GameInstance.h"

ACharacterSelectPlayerController::ACharacterSelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;

	HitActor = nullptr;

	static ConstructorHelpers::FClassFinder<UUserWidget> SelectWidgetClassRef(TEXT("/Game/Project_A/Blueprint/CharacterSelect/UI_Select.UI_Select_C"));
	
	if (SelectWidgetClassRef.Succeeded())
	{
		SelectWidgetClass = SelectWidgetClassRef.Class;
	}

}

void ACharacterSelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SelectWidget = CreateWidget<USelectWidget>(GetWorld(), SelectWidgetClass);
	SelectWidget->AddToViewport();

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
			// HitActor가 없다가 생기면 true
			SelectWidget->SetStartButtonEnable(true);

			GetWorld()->GetGameInstance<UPA_GameInstance>()->SetPlayerType(SelectPlayer->GetPlayerType());
		}
	}
	else
	{
		// HitActor가 있다가 없어지면 다시 false
		SelectWidget->SetStartButtonEnable(false);
	}
}
