// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AILichProjectile.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;
class AEffectBase;

UCLASS()
class PROJECT_A_API AAILichProjectile : public AActor
{
	GENERATED_BODY()

public:
	AAILichProjectile();

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VIsibleAnywhere, Category = Sphere)
	USphereComponent* SphereTrigger;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	AEffectBase* NiagaraEffect;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* Projectile;

#if WITH_EDITORONLY_DATA
	UArrowComponent* Arrow;
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; 
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
