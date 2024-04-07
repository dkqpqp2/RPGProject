// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_MonsterHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/PA_MonsterWidgetInterface.h"

UPA_MonsterHpBarWidget::UPA_MonsterHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UPA_MonsterHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("M_PbHpBar")));
	ensure(HpProgressBar);

	IPA_MonsterWidgetInterface* MonsterWidget = Cast<IPA_MonsterWidgetInterface>(OwningActor);
	if (MonsterWidget)
	{
		MonsterWidget->SetupMonsterWidget(this);
	}
}

void UPA_MonsterHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}
