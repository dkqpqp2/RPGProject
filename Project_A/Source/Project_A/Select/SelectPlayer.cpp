// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Capsule;

	Mesh->SetupAttachment(Capsule);

	Capsule->bVisualizeComponent = true;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Capsule->SetCollisionProfileName(TEXT("PACapsule"));

}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

