// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "PA_AIController.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackEnd = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MonsterCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MonsterCapsule"));
	MonsterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MonsterMesh"));

	MonsterMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MonsterMovement"));

	RootComponent = MonsterCapsule;

	MonsterMesh->SetupAttachment(MonsterCapsule);
	MonsterMovement->SetUpdatedComponent(MonsterCapsule);

	//AIControllerClass = APA_AIController::StaticClass();
	static ConstructorHelpers::FClassFinder<AAIController> AIControllerClassRef(TEXT("/Game/Project_A/Blueprint/AI/BP_PA_AIController.BP_PA_AIController_C"));
	if (AIControllerClassRef.Class)
	{
		AIControllerClass = AIControllerClassRef.Class;
	}

}

void AAIPawn::ChangeAIAnimType(uint8 AnimType)
{
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAIPawn::GetAIPatrolRadius()
{
	return 500.0f;
}

float AAIPawn::GetAIDetectRange()
{
	return 0.0f;
}

float AAIPawn::GetAIAttackRange()
{
	return 0.0f;
}

float AAIPawn::GetAITurnSpeed()
{
	return 0.0f;
}


