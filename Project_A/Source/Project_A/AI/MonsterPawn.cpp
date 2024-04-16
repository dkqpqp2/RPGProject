// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "PA_AIController.h"
#include "MonsterAnimInstance.h"
#include "AI/AIStat/AIMonsterStatData.h"
#include "GameFramework/FloatingPawnMovement.h"

AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = APA_AIController::StaticClass();

}


void AMonsterPawn::ChangeAIAnimType(uint8 AnimType)
{
	MonsterAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();


}

void AMonsterPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

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
