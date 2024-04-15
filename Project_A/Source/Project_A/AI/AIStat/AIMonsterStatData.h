#pragma once

#include "../../GameInfo.h"
#include "Engine/DataTable.h"
#include "AIMonsterStatData.generated.h"


UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	BasicMonster,
	MiddleMonster,
	BossMonster

};

USTRUCT(BlueprintType)
struct FAIMonsterStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EMonsterType Type;

	UPROPERTY(EditAnywhere)
	FString MonsterName;

	UPROPERTY(EditAnywhere)
	float Level;

	UPROPERTY(EditAnywhere)
	float MaxHp;

	UPROPERTY(EditAnywhere)
	float AttackDamage;

	UPROPERTY(EditAnywhere)
	float MonsterArmor;

	UPROPERTY(EditAnywhere)
	float AttackSpeed;

	UPROPERTY(EditAnywhere)
	float AttackDistance;

	UPROPERTY(EditAnywhere)
	float TraceDistance;

	UPROPERTY(EditAnywhere)
	float MonsterExp;  
};