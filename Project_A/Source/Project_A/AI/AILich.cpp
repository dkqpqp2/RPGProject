// Fill out your copyright notice in the Description page of Project Settings.


#include "AILich.h"
#include "PA_AIController.h"
#include "MonsterAnimInstance.h"

AAILich::AAILich()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MonsterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/UndeadPack/Lich/Mesh/SK_Lich.SK_Lich'"));
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
	
	MonsterCapsule->SetCapsuleHalfHeight(96.0f);
	MonsterCapsule->SetCapsuleRadius(42.0f);


	AIControllerClass = APA_AIController::StaticClass();

}
