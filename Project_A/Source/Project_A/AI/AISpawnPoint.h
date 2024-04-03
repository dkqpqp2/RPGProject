// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnPoint.generated.h"

UCLASS()
class PROJECT_A_API AAISpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawnPoint();

protected:
	USceneComponent* Root;

#if WITH_EDITORONLY_DATA
	UArrowComponent* Arrow;
#endif

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIPawn> SpawnClass;

	class AAIPawn* SpawnAI;

	UPROPERTY(EditAnywhere)
	float SpawnTime;

	float AccTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

public:
	void ClearSpawnObject();

};
