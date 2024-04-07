// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_MonsterWidgetComponent.h"
#include "AI/AIUI/PA_MonsterWidget.h"

void UPA_MonsterWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UPA_MonsterWidget* PA_MonsterWidget = Cast<UPA_MonsterWidget>(GetWidget());
	if (PA_MonsterWidget)
	{
		PA_MonsterWidget->SetOwningActor(GetOwner());
	}


}
