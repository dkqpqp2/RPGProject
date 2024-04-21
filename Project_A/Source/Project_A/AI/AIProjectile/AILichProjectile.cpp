// Fill out your copyright notice in the Description page of Project Settings.


#include "AILichProjectile.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Effect/EffectBase.h"
#include "Components/ArrowComponent.h"
#include "AI/PA_AIController.h"
#include "Character/PA_CharacterBase.h"

// Sets default values
AAILichProjectile::AAILichProjectile()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

#if WITH_EDITORONLY_DATA
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	Arrow->SetupAttachment(Mesh);

#endif

	RootComponent = Mesh;
	SphereTrigger->SetupAttachment(Mesh);
	SphereTrigger->SetCollisionProfileName(TEXT("EnemyAttack"));
	Mesh->SetCollisionProfileName(TEXT("EnemyAttack"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Organic/StaticMesh/SM_Plains_LargeRock02.SM_Plains_LargeRock02'"));
	if (StaticMeshRef.Object)
	{
		Mesh->SetStaticMesh(StaticMeshRef.Object);
	};
	Mesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	float RandomSpeed = FMath::RandRange(1.0f, 3.0f);

	Projectile->InitialSpeed = 100.0f * RandomSpeed;
	Projectile->MaxSpeed = 3500.0f;
	SphereTrigger->SetSphereRadius(600.0f);

}

// Called when the game starts or when spawned
void AAILichProjectile::BeginPlay()
{
	Super::BeginPlay();

	//APA_CharacterBase* Player = Cast<APA_CharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//FVector ProjectileLocation = GetActorLocation();
	//FVector TargetLocation = Player->GetActorLocation();
	//FVector Dir = TargetLocation - ProjectileLocation;

	//Dir.Z = 0.0;
	//FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
	//Rot.Pitch = 0.0;
	//Rot.Roll = 0.0;
	//SphereTrigger->SetRelativeRotation(Rot);

}

// Called every frame
void AAILichProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AAILichProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	FCollisionQueryParams Params(NAME_None, false, this);


	FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FVector EndLocation = StartLocation + GetActorForwardVector() * 150.0f;

	FHitResult HitResult;
	bool IsCollision = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(50.0f), Params);

	FString CollisionName = Other->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Other : %s"), *CollisionName));

	APA_CharacterBase* Player = Cast<APA_CharacterBase>(Other);
	if (Other && Player)
	{
		FActorSpawnParameters ParamResult;
		FDamageEvent DmgEvent;
		//HitResult.GetActor()->TakeDamage(0.f, DmgEvent, Player->GetController(), this);
		ParamResult.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ParamResult);

		Effect->SetNiagaraAsset(FSoftObjectPath(TEXT("/Game/KTP_Effect/Particles/Fly/Explosion_01_01.Explosion_01_01")));
		Destroy();
	}

	else if (Other && !Player)
	{
		FActorSpawnParameters ParamResult;

		ParamResult.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), ParamResult);

		Effect->SetNiagaraAsset(FSoftObjectPath(TEXT("/Game/KTP_Effect/Particles/Fly/Explosion_01_01.Explosion_01_01")));
		Destroy();
	}
	

}

