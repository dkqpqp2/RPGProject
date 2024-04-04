// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AILichProjectile.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;

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

	UPROPERTY(VisibleAnywhere, Category = Particle)
	UNiagaraComponent* Niagara;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* Projectile;



	
public:	
	// Sets default values for this actor's properties
	AAILichProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
