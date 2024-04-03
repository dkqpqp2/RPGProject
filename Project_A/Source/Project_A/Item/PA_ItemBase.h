// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PA_ItemBase.generated.h"

UCLASS()
class PROJECT_A_API APA_ItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APA_ItemBase();
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<class USphereComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UParticleSystemComponent> Effect;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OthderBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);
	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);
};
