// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PA_CharacterData.h"
#include "PA_GameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPAGameSingleton, Error, All);
/**
 * 
 */
UCLASS()
class PROJECT_A_API UPA_GameSingleton : public UObject
{
	GENERATED_BODY()
public:
	UPA_GameSingleton();

	static UPA_GameSingleton& Get();

public:
	FPA_CharacterData GetCharacterData(int32 InLevel) const { return CharacterDataTable.IsValidIndex(InLevel - 1) ? CharacterDataTable[InLevel - 1] : FPA_CharacterData(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FPA_CharacterData> CharacterDataTable;


};
