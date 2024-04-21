// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SelectPlayer.generated.h"

UCLASS()
class PROJECT_A_API ASelectPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectPlayer();

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	class USelectAnimInstance* AnimInst;

	UPROPERTY(EditAnywhere)
	EPlayerType PlayerType;

public:
	EPlayerType GetPlayerType()
	{
		return PlayerType;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelect(bool InSelect);
};
