// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "PA_AIController.h"
#include "MonsterAnimInstance.h"
#include "AI/AIStat/AIMonsterStatData.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AI/AIStat/MonsterState.h"

UDataTable* AMonsterPawn::MonsterDataTable = nullptr;

const FAIMonsterStatData* AMonsterPawn::FindMonsterData(const FString& Name)
{
	return MonsterDataTable->FindRow<FAIMonsterStatData>(*Name, TEXT(""));
}

AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	State = CreateDefaultSubobject<UMonsterState>(TEXT("MonsterState"));

	AIControllerClass = APA_AIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterTableRef(TEXT("/Script/Engine.DataTable'/Game/Project_A/Blueprint/AI/DT_MonsterDataTable.DT_MonsterDataTable'"));
	if (!IsValid(MonsterDataTable) && MonsterTableRef.Succeeded())
	{
		MonsterDataTable = MonsterTableRef.Object;
	}

}


void AMonsterPawn::ChangeAIAnimType(uint8 AnimType)
{
	MonsterAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	MonsterAnimInst = Cast<UMonsterAnimInstance>(MonsterMesh->GetAnimInstance());

	FAIMonsterStatData* MonsterData = MonsterDataTable->FindRow<FAIMonsterStatData>(*TableRowName, TEXT(""));

	if (MonsterData)
	{

	}

}

void AMonsterPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	State->DataTableRowName = TableRowName;
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMonsterPawn::NormalAttack()
{

}

void AMonsterPawn::NormalAttack_B()
{
}

void AMonsterPawn::SkillA()
{
}
