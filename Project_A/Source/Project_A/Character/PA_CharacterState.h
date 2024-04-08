// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "PA_CharacterState.generated.h"


UENUM(BlueprintType)
enum class ECharacterJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	ECharacterJob Job;

	UPROPERTY(EditAnywhere)
	int32	AttachDamage;

	UPROPERTY(EditAnywhere)
	int32	ArmorPoint;

	UPROPERTY(EditAnywhere)
	int32	MaxHp;

	UPROPERTY(EditAnywhere)
	int32	MaxMp;

	UPROPERTY(EditAnywhere)
	float	MoveSpeed;

	UPROPERTY(EditAnywhere)
	float	AttackSpeed;

	UPROPERTY(EditAnywhere)
	float	AttackDistance;
};


UCLASS()
class PROJECT_A_API APA_CharacterState : public APlayerState
{
	GENERATED_BODY()

public:
	APA_CharacterState();

private:
	UDataTable* CharacterDataTable;
	
public:
	FString Name;
	ECharacterJob Job;
	int32	AttachDamage;
	int32	ArmorPoint;
	int32	Hp;
	int32	MaxHp;
	int32	Mp;
	int32	MaxMp;
	int32	Level;
	int32	Exp;
	float	MoveSpeed;
	float	AttackSpeed;
	float	AttackDistance;

protected:
	virtual void BeginPlay() override;

};
