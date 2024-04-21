// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_KnightCharacter.h"
#include "../Physics/PA_Collision.h"
#include "Components/SceneCaptureComponent2D.h"

APA_KnightCharacter::APA_KnightCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_PACAPSULE);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	FaceCapture->SetRelativeLocation(FVector(0.0, 76.0, 143.0));
	FaceCapture->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimaInstanceClassRef(TEXT("/Game/Project_A/Animation/ABP_PA_PlayerKnight.ABP_PA_PlayerKnight_C"));
	if (AnimaInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimaInstanceClassRef.Class);
	}
}
