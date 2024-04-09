// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_ExpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/PA_CharacterWidgetInterface.h"

UPA_ExpBarWidget::UPA_ExpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxExp = -1.0f;
}

void UPA_ExpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbExpBar")));
	ensure(ExpProgressBar);
	IPA_CharacterWidgetInterface* CharacterWidget = Cast<IPA_CharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UPA_ExpBarWidget::UpdateExpBar(float NewCurrentExp)
{
	ensure(MaxExp > 0.0f);
	if (ExpProgressBar)
	{
		ExpProgressBar->SetPercent(NewCurrentExp / MaxExp);
	}

}
