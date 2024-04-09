// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_HUDWidget.h"
#include "Interface/PA_CharacterHUDInterface.h"
#include "PA_HpBarWidget.h"
#include "PA_ExpBarWidget.h"
#include "PA_CharacterStatWidget.h"

UPA_HUDWidget::UPA_HUDWidget(const FObjectInitializer& ObjectInitializer)  : Super(ObjectInitializer)
{

}

void UPA_HUDWidget::UpdateStat(const FPA_CharacterData& BaseStat, const FPA_CharacterData& ModifierStat)
{

	FPA_CharacterData TotalStat = BaseStat + ModifierStat;
	HpBar->SetMaxHp(TotalStat.MaxHp);
	ExpBar->SetMaxExp(TotalStat.MaxExp);

//	CharacterStat->UpdateStat(BaseStat, ModifierStat);
	
}

void UPA_HUDWidget::UpdateHpBar(float NewCurrentHp)
{
	HpBar->UpdateHpBar(NewCurrentHp);
}

void UPA_HUDWidget::UpdateExpBar(float NewCurrentExp)
{
	ExpBar->UpdateExpBar(NewCurrentExp);
}

void UPA_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UPA_HpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
	CharacterStat = Cast<UPA_CharacterStatWidget>(GetWidgetFromName(TEXT("WidgetCharacterStat")));
	ExpBar = Cast<UPA_ExpBarWidget>(GetWidgetFromName(TEXT("WidgetExpBar")));

	IPA_CharacterHUDInterface* HUDPawn = Cast<IPA_CharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}

}

