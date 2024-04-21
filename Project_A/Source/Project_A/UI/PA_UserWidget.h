// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "PA_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
	
};
