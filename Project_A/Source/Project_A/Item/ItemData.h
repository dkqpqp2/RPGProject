// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class ENewItemType : uint8
{
	Weapon,
	Potion,
	Scroll
};

/**
 * 
 */
UCLASS()
class PROJECT_A_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	ENewItemType Type;
	
};
