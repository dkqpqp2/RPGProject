// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

// Sets default values
AEffectBase::AEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	RootComponent = Particle;

	Audio->SetupAttachment(Particle);

	Particle->bVisualizeComponent = true;

}

// Called when the game starts or when spawned
void AEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectBase::SetParticleAsset(const FString& Path)
{
	UParticleSystem* InParticle = LoadObject<UParticleSystem>(nullptr, *Path);
	SetParticleAsset(InParticle);
}

void AEffectBase::SetParticleAsset(UParticleSystem* InParticle)
{
	if (IsValid(InParticle))
	{
		Particle->SetTemplate(InParticle);
		Particle->OnSystemFinished.AddDynamic(this, &AEffectBase::OnParticleFinish);
	}
}

void AEffectBase::SetSoundAsset(const FString& Path)
{
	USoundBase* InSound = LoadObject<USoundBase>(nullptr, *Path);

	SetSoundAsset(InSound);
}

void AEffectBase::SetSoundAsset(USoundBase* InSound)
{
	if (IsValid(InSound))
	{
		Audio->SetSound(InSound);
		Audio->Play();
	}
}

void AEffectBase::OnParticleFinish(UParticleSystemComponent* InParticle)
{
	Destroy();
}

