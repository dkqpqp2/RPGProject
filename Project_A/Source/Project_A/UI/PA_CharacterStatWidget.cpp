// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterStatWidget.h"
#include "GameData/PA_CharacterData.h"
#include "Components/TextBlock.h"

void UPA_CharacterStatWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPA_CharacterStatWidget::UpdateStat(const FPA_CharacterData& BaseStat, const FPA_CharacterData& ModifierStat)
{
	/*for (TFieldIterator<FNumericProperty> PropIt(FPA_CharacterData::StaticStruct()); PropIt; ++PropIt)
	{
		const FName PropKey(PropIt->GetName());

		float BaseData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&BaseStat, &BaseData);
		float ModifierData = 0.0f;
		PropIt->GetValue_InContainer((const void*)&ModifierStat, &ModifierData);

		UTextBlock** BaseTextBlockPtr = BaseLookup.Find(PropKey);
		if (BaseTextBlockPtr)
		{
			(*BaseTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(BaseData)));
		}

		UTextBlock** ModifierTextBlockPtr = ModifierLookup.Find(PropKey);
		if (ModifierTextBlockPtr)
		{
			(*ModifierTextBlockPtr)->SetText(FText::FromString(FString::SanitizeFloat(ModifierData)));
		}
	}*/

	float BaseAttackDamageData = BaseStat.AttackDamage;
	float ModifierAttackDamageData = ModifierStat.AttackDamage;
	float BaseMaxHpData = BaseStat.MaxHp;
	float ModifierMaxHpData = ModifierStat.MaxHp;
	float BaseAttackRangeData = BaseStat.AttackRange;
	float ModifierAttackRangeData = ModifierStat.AttackRange;
	float BaseAttackSpeedData = BaseStat.AttackSpeed;
	float ModifierAttackSpeedData = ModifierStat.AttackSpeed;
	float BaseMovementSpeedData = BaseStat.MovementSpeed;
	float ModifierMovementSpeedData = ModifierStat.MovementSpeed;

	TxtAttackDamageBase->SetText(FText::FromString(FString::SanitizeFloat(BaseAttackDamageData)));
	TxtAttackDamageModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierAttackDamageData)));
	TxtMaxHpBase->SetText(FText::FromString(FString::SanitizeFloat(BaseMaxHpData)));
	TxtMaxHpModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierMaxHpData)));
	TxtAttackRangeBase->SetText(FText::FromString(FString::SanitizeFloat(BaseAttackRangeData)));
	TxtAttackRangeModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierAttackRangeData)));
	TxtAttackSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseAttackSpeedData)));
	TxtAttackSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierAttackSpeedData)));
	TxtMovementSpeedBase->SetText(FText::FromString(FString::SanitizeFloat(BaseMovementSpeedData)));
	TxtMovementSpeedModifier->SetText(FText::FromString(FString::SanitizeFloat(ModifierMovementSpeedData)));


}
