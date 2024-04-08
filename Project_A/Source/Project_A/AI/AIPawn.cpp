// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "PA_AIController.h"
#include "AISpawnPoint.h"
#include "MonsterAnimInstance.h"
#include "AI/AIStat/PA_MonsterStatComponent.h"
#include "AI/AIUI/PA_MonsterWidgetComponent.h"
#include "AI/AIUI/PA_MonsterHpBarWidget.h"
#include "Components/WidgetComponent.h"

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

	SpawnPoint = nullptr;
	
	Stat = CreateDefaultSubobject<UPA_MonsterStatComponent>(TEXT("Stat"));
	HpBar = CreateDefaultSubobject<UPA_MonsterWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/Project_A/UI/WBP_MonsterHpBar.WBP_MonsterHpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}



}

void AAIPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &AAIPawn::SetDead);

}

void AAIPawn::ChangeAIAnimType(uint8 AnimType)
{
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (SpawnPoint)
	{
		SpawnPoint->ClearSpawnObject(); 
	}
}

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Dmg : %.2f"), DamageAmount));

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AAIPawn::SetupMonsterWidget(UPA_MonsterWidget* InMonsterWidget)
{
	UPA_MonsterHpBarWidget* HpBarWidget = Cast<UPA_MonsterHpBarWidget>(InMonsterWidget);

	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetMaxHp());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UPA_MonsterHpBarWidget::UpdateHpBar);
	}
}

void AAIPawn::SetDead()
{
	ChangeAIAnimType(static_cast<uint8>(EMonsterAnimType::Death));
	SetActorEnableCollision(false);
	HpBar->SetHiddenInGame(true);
}





