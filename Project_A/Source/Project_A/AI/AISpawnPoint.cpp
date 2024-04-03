// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"
#include "Components/ArrowComponent.h"
#include "AI/AIPawn.h"

// Sets default values
AAISpawnPoint::AAISpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

#if WITH_EDITORONLY_DATA
	 Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	 Arrow->SetupAttachment(Root);

#endif

	RootComponent = Root;
	Root->bVisualizeComponent = true;

	SpawnAI = nullptr;
	AccTime = 0.0f;
	SpawnTime = 0.0f;
}

void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}

void AAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAISpawnPoint::Spawn()
{
	if (!IsValid(SpawnClass))
	{
		return;
	}
	FActorSpawnParameters SpawnParam;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAIPawn* DefaultObj = Cast<AAIPawn>(SpawnClass->GetDefaultObject());

	float HalfHeight = 0.0f;

	if (IsValid(DefaultObj))
	{
		HalfHeight = DefaultObj->GetHalfHeight();
	}

	SpawnAI = GetWorld()->SpawnActor<AAIPawn>(SpawnClass, GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight), GetActorRotation(), SpawnParam);

}


