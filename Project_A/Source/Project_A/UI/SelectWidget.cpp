// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"



void USelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStartButton")));

	StartButton->OnClicked.AddDynamic(this, &USelectWidget::StartButtonClick);


}

void USelectWidget::SetStartButtonEnable(bool InEnable)
{
	// 활성화 비활성화를 다를 수 있는 함수
	StartButton->SetIsEnabled(InEnable);




}

void USelectWidget::StartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}
