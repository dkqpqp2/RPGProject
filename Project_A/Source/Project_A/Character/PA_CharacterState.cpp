// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterState.h"

APA_CharacterState::APA_CharacterState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterDataRef(TEXT("/Script/Engine.DataTable'/Game/Project_A/Blueprint/PA_CharacterData.PA_CharacterData'"));
	if (CharacterDataRef.Object)
	{
		CharacterDataTable = CharacterDataRef.Object;
	}
}

void APA_CharacterState::BeginPlay()
{
	Super::BeginPlay();

	FCharacterData* CharacterData = CharacterDataTable->FindRow<FCharacterData>(TEXT("Knight"), TEXT(""));
	if (CharacterData)
	{
		Job = CharacterData->Job;
		AttachDamage = CharacterData->AttachDamage;
		ArmorPoint = CharacterData->ArmorPoint;
		Hp = CharacterData->MaxHp;
		MaxHp = CharacterData->MaxHp;
		Mp = CharacterData->MaxMp;
		MaxMp = CharacterData->MaxMp;
		MoveSpeed = CharacterData->MoveSpeed;
		AttackSpeed = CharacterData->AttackSpeed;
		AttackDistance = CharacterData->AttackDistance;

		Level = 1;
		Exp = 0;
	}

}
