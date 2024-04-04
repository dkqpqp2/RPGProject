// Fill out your copyright notice in the Description page of Project Settings.


#include "AILichProjectile.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Effect/EffectBase.h"


// Sets default values
AAILichProjectile::AAILichProjectile()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	RootComponent = Mesh;
	Niagara->SetupAttachment(Mesh);
	SphereTrigger->SetupAttachment(Mesh);
	Mesh->SetCollisionProfileName(TEXT("EnemyAttack"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/InfinityBladeWeapons/Weapons/Staff/StaticMesh/SM_Stf_StaffofAncients.SM_Stf_StaffofAncients'"));
	if (StaticMeshRef.Object)
	{
		Mesh->SetStaticMesh(StaticMeshRef.Object);
	}

	

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

