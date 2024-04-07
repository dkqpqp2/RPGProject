// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_WidgetComponent.h"
#include "PA_UserWidget.h"

void UPA_WidgetComponent::InitWidget()
{
	Super::InitWidget();

	UPA_UserWidget* PAUserWidget = Cast<UPA_UserWidget>(GetWidget());
	if (PAUserWidget)
	{
		PAUserWidget->SetOwningActor(GetOwner());
	}


}
