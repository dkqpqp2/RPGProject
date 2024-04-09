// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "PA_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API APA_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APA_PlayerController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UPA_HUDWidget> PA_HUDWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class UPA_HUDWidget> PA_HUDWidget;
};
