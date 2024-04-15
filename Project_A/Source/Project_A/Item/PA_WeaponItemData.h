// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Item/PA_ItemData.h"
#include "GameData/PA_CharacterData.h"
#include "PA_WeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_WeaponItemData : public UPA_ItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSoftObjectPtr<class USkeletalMesh> WeaponMesh;
	
	UPROPERTY(EditAnywhere, Category = Stat)
	FPA_CharacterData ModifierStat;

	UPROPERTY(EditAnywhere, Category = Stat)
	FPA_CharacterData ZeroStat;
};
