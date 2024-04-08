#pragma once

#include "../GameInfo.h"
#include "Engine/DataTable.h"
#include "PA_CharacterData.generated.h"

USTRUCT(BlueprintType)
struct FPA_CharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPA_CharacterData() : MaxHp(0.0f), AttackDamage(0.0f), AttackRange(0.0f), AttackSpeed(0.0f), MovementSpeed(0.0f), TraceDistance(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float TraceDistance;

	FPA_CharacterData operator+(const FPA_CharacterData& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FPA_CharacterData Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FPA_CharacterData) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}
		return Result;
	}
};