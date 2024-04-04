// Fill out your copyright notice in the Description page of Project Settings.


#include "AILichProjectile.h"

// Sets default values
AAILichProjectile::AAILichProjectile()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	RootComponent = Mesh;
	SphereTrigger->SetupAttachment(Mesh);
	Niagara->SetupAttachment(Mesh);
	Projectile->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned
void AAILichProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAILichProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

