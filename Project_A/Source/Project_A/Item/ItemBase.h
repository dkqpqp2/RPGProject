// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROJECT_A_API AItemBase : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AItemBase();


	UPROPERTY(EditAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Box)
	TObjectPtr<class UStaticMeshComponent> BoxMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TObjectPtr<class UWidgetComponent> Widget;

	UPROPERTY(EditAnywhere, Category = Effect)
	TObjectPtr<class UParticleSystemComponent> Effect;

	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UItemData> Item;

	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UItemComponent> ItemComponent;

protected:
	void FClickAction();

protected:
	virtual void Tick(float DeltaSeconds);


public:
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);
};
