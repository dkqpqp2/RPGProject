// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "GameFrameWork/FloatingPawnMovement.h"
#include "../Interface/PA_AIInterface.h"
#include "../Interface/PA_MonsterWidgetInterface.h"
#include "AIPawn.generated.h"

UCLASS()
class PROJECT_A_API AAIPawn : public APawn, public IPA_AIInterface, public IPA_MonsterWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

	virtual void PostInitializeComponents() override;

public:

	USkeletalMeshComponent* GetMesh() const 
	{
		return MonsterMesh;
	}

	float GetHalfHeight() const
	{
		return MonsterCapsule->GetScaledCapsuleHalfHeight();
	}
	float GetCapsuleRadius()
	{
		return MonsterCapsule->GetScaledCapsuleRadius();
	}


protected:
	UPROPERTY(EditAnywhere, Category = Monster)
	UCapsuleComponent* MonsterCapsule;

	UPROPERTY(EditAnywhere, Category = Monster)
	USkeletalMeshComponent* MonsterMesh;

	UPROPERTY(EditAnywhere, Category = Monster)
	UFloatingPawnMovement* MonsterMovement;

	bool AttackEnd;
	bool AttackRightEnd;

	class AAISpawnPoint* SpawnPoint;

public:
	void SetSpawnPoint(class AAISpawnPoint* Point)
	{
		SpawnPoint = Point;
	}


	TArray<UAnimMontage*> SkillList;

public:
	void SetAttackEnd(bool End)
	{
		AttackEnd = End;
	}

	bool IsAttackEnd()
	{
		return AttackEnd;
	}

	void SetAttackRightEnd(bool End)
	{
		AttackRightEnd = End;
	}

	bool IsAttackRightEnd()
	{
		return AttackRightEnd;
	}

public:
	virtual void ChangeAIAnimType(uint8 AnimType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetDead();

	float DeadEventDelaytime = 5.0f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPA_MonsterStatComponent> Stat;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPA_MonsterWidgetComponent> HpBar;

	virtual void SetupMonsterWidget(class UPA_MonsterWidget* InMonsterWidget) override;

};
