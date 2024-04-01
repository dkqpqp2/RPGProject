// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Engine/DataAsset.h"
#include "PA_ComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_ComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPA_ComboActionData();

	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount;
	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = ComboData)
	TArray<float> EFfecttiveFrameCount;


};
