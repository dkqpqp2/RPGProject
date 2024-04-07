// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterStatComponent.h"

// Sets default values for this component's properties
UPA_CharacterStatComponent::UPA_CharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHp = 200.0f;
	CurrentHp = MaxHp;
	// ...
}


// Called when the game starts
void UPA_CharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHp = MaxHp;
	
}

float UPA_CharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UPA_CharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}



