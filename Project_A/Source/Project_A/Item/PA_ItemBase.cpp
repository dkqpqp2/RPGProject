 // Fill out your copyright notice in the Description page of Project Settings.


#include "PA_ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/PA_Collision.h"
#include "Interface/PA_CharacterItemInterface.h"


// Sets default values
APA_ItemBase::APA_ItemBase()
{
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_PATRIGGER);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	Trigger->SetSphereRadius(50.0f, true);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APA_ItemBase::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_Glimmer/SK_Blade_Glimmer.SK_Blade_Glimmer'"));
	if (WeaponMeshRef.Object)
	{
		Mesh->SetSkeletalMesh(WeaponMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/Watermills/Particles/P_Water_Splashes.P_Water_Splashes'"));
	if (EffectRef.Object)
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}
}

void APA_ItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthderBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (nullptr == Item)
	{
		Destroy();
		return;
	}
	IPA_CharacterItemInterface* OverlappingPawn = Cast<IPA_CharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		OverlappingPawn->TakeItem(Item);
	}

	Effect->Activate(true);
	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->OnSystemFinished.AddDynamic(this, &APA_ItemBase::OnEffectFinished);
	
}

void APA_ItemBase::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}


