// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "ItemSoda.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API AItemSoda : public AItemBase
{
	GENERATED_BODY()

public:
	AItemSoda();

	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> Cap;

	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> Opener;
	
};
