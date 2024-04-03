// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "EffectBase.generated.h"

class UNiagaraComponent;

UCLASS()
class PROJECT_A_API AEffectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectBase();

protected:
	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* Audio;


	UPROPERTY(EditAnywhere, Category = Particle)
	UNiagaraComponent* Niagara;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetParticleAsset(const FString& Path);
	void SetParticleAsset(UParticleSystem* InParticle);

	void SetNiagaraAsset(const FSoftObjectPath& Path);
	
	void SetSoundAsset(const FString& Path);
	void SetSoundAsset(USoundBase* InSound);

	UFUNCTION()
	void OnParticleFinish(UParticleSystemComponent* InParticle);

	UFUNCTION()
	void OnNiagaraFinish(class UNiagaraComponent* InSystem);
};
