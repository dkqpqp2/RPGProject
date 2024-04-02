// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "GameFrameWork/FloatingPawnMovement.h"
#include "AIPawn.generated.h"

UCLASS()
class PROJECT_A_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

public:
	float GetHalfHeight() const
	{
		return MonsterCapsule->GetScaledCapsuleHalfHeight();
	}


protected:
	UPROPERTY(EditAnywhere, Category = Monster)
	UCapsuleComponent* MonsterCapsule;

	UPROPERTY(EditAnywhere, Category = Monster)
	USkeletalMeshComponent* MonsterMesh;

	UPROPERTY(EditAnywhere, Category = Monster)
	UFloatingPawnMovement* MonsterMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
