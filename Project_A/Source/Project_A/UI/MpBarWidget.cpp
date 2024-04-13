// Fill out your copyright notice in the Description page of Project Settings.


#include "MpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/PA_CharacterWidgetInterface.h"

UMpBarWidget::UMpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxMp = 100.0f;
}

void UMpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbMpBar")));
	ensure(MpProgressBar);
	
	IPA_CharacterWidgetInterface* CharacterWidget = Cast<IPA_CharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UMpBarWidget::UpdateMpBar(float NewCurrentMp)
{
	ensure(MaxMp > 0.0f);
	if (MpProgressBar)
	{
		MpProgressBar->SetPercent(NewCurrentMp / MaxMp);
	}
}
