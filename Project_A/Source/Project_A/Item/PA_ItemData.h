// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Engine/DataAsset.h"
#include "PA_ItemData.generated.h"


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
class PROJECT_A_API UPA_ItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	ENewItemType Type;
};
