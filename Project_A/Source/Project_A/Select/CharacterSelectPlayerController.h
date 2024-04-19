// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "CharacterSelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API ACharacterSelectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterSelectPlayerController();

protected:
	AActor* HitActor;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent()override;

public:
	virtual void Tick(float DeltaTime) override;
protected:
	void OnSelect(const FInputActionValue& Value);
};
