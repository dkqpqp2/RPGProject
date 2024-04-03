// Fill out your copyright notice in the Description page of Project Settings.


#include "AILich.h"
#include "PA_AIController.h"
#include "MonsterAnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "../Effect/EffectBase.h"

AAILich::AAILich()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MonsterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/UndeadPack/Lich/Mesh/SK_Lich_Full.SK_Lich_Full'"));
	if (MonsterMeshRef.Object)
	{
		MonsterMesh->SetSkeletalMesh(MonsterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MonsterAnimInstanceRef(TEXT("/Game/Project_A/Animation/AI/AB_Lich.AB_Lich_C"));
	if (MonsterAnimInstanceRef.Class)
	{
		MonsterMesh->SetAnimInstanceClass(MonsterAnimInstanceRef.Class);
	}

	MonsterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -108.0f));
	MonsterMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	MonsterMesh->SetCollisionProfileName(TEXT("Pawn"));

	MonsterCapsule->SetCapsuleHalfHeight(96.0f);
	MonsterCapsule->SetCapsuleRadius(42.0f);

}

void AAILich::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInst = Cast<UMonsterAnimInstance>(MonsterMesh->GetAnimInstance());

}

void AAILich::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAILich::NormalAttack()
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
		HitResult.GetActor()->TakeDamage(10.f, DmgEvent, GetController(), this);

		FActorSpawnParameters ParamResult;

		ParamResult.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ParamResult);

		Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/UndeadPack/Lich/Particles/P_Smoke_FX.P_Smoke_FX'"));
		//Effect->SetSoundAsset(TEXT(""));
	}

}

void AAILich::NormalAttack_B()
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
		HitResult.GetActor()->TakeDamage(20.f, DmgEvent, GetController(), this);

		FActorSpawnParameters ParamResult;

		ParamResult.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ParamResult);

		Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/UndeadPack/Lich/Particles/P_Smoke_FX.P_Smoke_FX'"));
		//Effect->SetSoundAsset(TEXT(""));
	}
}
