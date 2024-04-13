// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGoblin.h"
#include "PA_AIController.h"
#include "MonsterAnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "../Effect/EffectBase.h"
#include "Physics/PA_Collision.h"

AAIGoblin::AAIGoblin
()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GoblinMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/UndeadPack/EnemyGoblin/Mesh/SM_EnemyGoblin.SM_EnemyGoblin'"));
	if (GoblinMeshRef.Object)
	{
		MonsterMesh->SetSkeletalMesh(GoblinMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/Project_A/Animation/AI/AM_Goblin.AM_Goblin_C"));
	if (AnimInstanceRef.Class)
	{
		MonsterMesh->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	MonsterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	MonsterMesh->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));
	MonsterMesh->SetCollisionProfileName(TEXT("NoCollision"));

	MonsterCapsule->SetCapsuleHalfHeight(55.0f);
	MonsterCapsule->SetCapsuleRadius(35.0f);
	MonsterCapsule->SetCollisionProfileName(CPROFILE_PAMONSTERCAPSULE);

	MonsterMovement->MaxSpeed = 500.0f;

	SetMonsterExp(10.0);

}

void AAIGoblin::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInst = Cast<UMonsterAnimInstance>(MonsterMesh->GetAnimInstance());
}
void AAIGoblin::NormalAttack()
{
	FCollisionQueryParams Params(NAME_None, false, this);

	FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FVector EndLocation = StartLocation + GetActorForwardVector() * 150.0f;

	FHitResult HitResult;
	bool IsCollision = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(50.0f), Params);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = IsCollision ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.0f, 75.0f, 50.0f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 3.0f);

#endif


	if (IsCollision)
	{
		FDamageEvent DmgEvent;
		HitResult.GetActor()->TakeDamage(0.f, DmgEvent, GetController(), this);

		FActorSpawnParameters ParamResult;

		ParamResult.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ParamResult);

		Effect->SetNiagaraAsset(FSoftObjectPath(TEXT("/Game/KTP_Effect/Particles/Fly/Expolison_06_02.Expolison_06_02")));
		//Effect->SetSoundAsset(TEXT(""));
	}

}

void AAIGoblin::NormalAttack_B()
{
	FCollisionQueryParams Params(NAME_None, false, this);

	FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FVector EndLocation = StartLocation + GetActorForwardVector() * 150.0f;

	FHitResult HitResult;
	bool IsCollision = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(50.0f), Params);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = IsCollision ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.0f, 75.0f, 50.0f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 3.0f);

#endif


	if (IsCollision)
	{
		FDamageEvent DmgEvent;
		HitResult.GetActor()->TakeDamage(0.f, DmgEvent, GetController(), this);

		FActorSpawnParameters ParamResult;

		ParamResult.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ParamResult);

		Effect->SetNiagaraAsset(FSoftObjectPath(TEXT("/Game/KTP_Effect/Particles/Fly/Expolison_09_09.Expolison_09_09")));
		//Effect->SetSoundAsset(TEXT(""));
	}
}

void AAIGoblin::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelaytime, false);
}