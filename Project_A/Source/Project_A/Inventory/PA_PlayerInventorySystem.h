// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "Item/S_Item.h"
#include "S_Slot.h"
#include "PA_PlayerInventorySystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_A_API UPA_PlayerInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPA_PlayerInventorySystem();

protected:

	int32 InventorySize;
	FS_Slot Slot;
	bool IsAddFailed;

	void AddItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
