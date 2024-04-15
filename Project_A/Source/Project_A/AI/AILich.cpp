// Fill out your copyright notice in the Description page of Project Settings.


#include "AILich.h"
#include "PA_AIController.h"
#include "MonsterAnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "../Effect/EffectBase.h"
#include "Physics/PA_Collision.h"
#include "AIProjectile/AILichProjectile.h"
#include "AI/AIUI/PA_MonsterWidgetComponent.h"

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
	MonsterMesh->SetCollisionProfileName(TEXT("NoCollision"));

	MonsterCapsule->SetCapsuleHalfHeight(96.0f);
	MonsterCapsule->SetCapsuleRadius(42.0f);
	MonsterCapsule->SetCollisionProfileName(CPROFILE_PAMONSTERCAPSULE);
	
	MonsterMovement->MaxSpeed = 450.f;

	TableRowName = TEXT("Lich");

	//수정 HpBarZOffset
	//HpBarZOffset = 230.0f;
	//HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, HpBarZOffset));

	//수정 MonsterExp
	//MonsterExp = 101.0f;
	//SetMonsterExp(MonsterExp);
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

		Effect->SetNiagaraAsset(FSoftObjectPath(TEXT("/Game/KTP_Effect/Particles/Fly/Expolison_03_01.Expolison_03_01")));
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

		Effect->SetNiagaraAsset(FSoftObjectPath(TEXT("/Game/KTP_Effect/Particles/Fly/Explosion_01_01.Explosion_01_01")));
		//Effect->SetSoundAsset(TEXT(""));
	}
}


void AAILich::SetDead()
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

