// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_GameSingleton.h"

DEFINE_LOG_CATEGORY(LogPAGameSingleton);

UPA_GameSingleton::UPA_GameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/Project_A/GameData/PA_CharacterData.PA_CharacterData'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterDataTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FPA_CharacterData*>(Value);
			}
		);
	}
	CharacterMaxLevel = CharacterDataTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UPA_GameSingleton& UPA_GameSingleton::Get()
{
	UPA_GameSingleton* Singleton = CastChecked<UPA_GameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogPAGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UPA_GameSingleton>();
}
