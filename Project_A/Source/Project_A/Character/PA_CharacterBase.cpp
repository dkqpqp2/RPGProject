// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Character/PA_CharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "PA_ComboActionData.h"
#include "Physics/PA_Collision.h"
#include "CharacterStat/PA_CharacterStatComponent.h"
#include "UI/PA_WidgetComponent.h"
#include "UI/PA_HpBarWidget.h"
#include "UI/MpBarWidget.h"
#include "UI/PA_ExpBarWidget.h"
#include "Item/PA_WeaponItemData.h"
#include "PA_CharacterState.h"
#include "Inventory/PA_PlayerInventorySystem.h"

DEFINE_LOG_CATEGORY(LogPACharacter);


// Sets default values
APA_CharacterBase::APA_CharacterBase()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_PACAPSULE);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	FaceCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("FaceCapture"));
	FaceCapture->SetupAttachment(GetMesh());
	FaceCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	FaceCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimaInstanceClassRef(TEXT("/Game/Project_A/Animation/ABP_PA_Character.ABP_PA_Character_C"));
	if (AnimaInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimaInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UPA_CharacterControlData> ShoulderDataRef(TEXT("/Script/Project_A.PA_CharacterControlData'/Game/Project_A/CharacterControl/PAC_Shoulder.PAC_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}


	static ConstructorHelpers::FObjectFinder<UPA_CharacterControlData> QuaterDataRef(TEXT("/Script/Project_A.PA_CharacterControlData'/Game/Project_A/CharacterControl/PAC_Quater.PAC_Quater'"));
	if (QuaterDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Project_A/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UPA_ComboActionData> ComboActionDataRef(TEXT("/Script/Project_A.PA_ComboActionData'/Game/Project_A/CharacterAction/PA_ComboAttack.PA_ComboAttack'"));
	if (ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Project_A/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> FaceTargetRef(TEXT("/Script/Engine.TextureRenderTarget2D'/Game/Project_A/Blueprint/RT_PlayerFace.RT_PlayerFace'"));
	if (FaceTargetRef.Succeeded())
	{
		FaceCapture->TextureTarget = FaceTargetRef.Object;
	}

	

	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &APA_CharacterBase::EquipWeapon)));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rSocket"));

	Stat = CreateDefaultSubobject<UPA_CharacterStatComponent>(TEXT("Stat"));

	HpBar = CreateDefaultSubobject<UPA_WidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/Project_A/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	Inventory = CreateDefaultSubobject<UPA_PlayerInventorySystem>(TEXT("Inventory"));

	
}

void APA_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &APA_CharacterBase::SetDead);

	FaceCapture->ShowOnlyActors.Add(this);
}

void APA_CharacterBase::SetCharacterControlData(const UPA_CharacterControlData* CharacterControlData)
{
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMvement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void APA_CharacterBase::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}

void APA_CharacterBase::ComboActionBegin()
{
	CurrentCombo = 1;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
	

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &APA_CharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();

}

void APA_CharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APA_CharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EFfecttiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = Stat->GetTotalStat().AttackSpeed;
	float ComboEffectiveTime = (ComboActionData->EFfecttiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &APA_CharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void APA_CharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		SetComboCheckTimer();
		HasNextComboCommand = false;
	}
}

void APA_CharacterBase::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	APA_CharacterState* State = GetPlayerState<APA_CharacterState>();

	const float AttackRange = Stat->GetTotalStat().AttackRange;
	const float AttackRadius = 50.0f;
	const float AttackDamage = Stat->GetTotalStat().AttackDamage;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_PAACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (HitDetected)
	{
		FDamageEvent DmgEvent;

		OutHitResult.GetActor()->TakeDamage(AttackDamage, DmgEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) + 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);


#endif
}


float APA_CharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Dmg : %.2f"), DamageAmount));

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void APA_CharacterBase::SetupCharacterWidget(UPA_UserWidget* InUserWidget)
{
	UPA_HpBarWidget* HpBarWidget = Cast<UPA_HpBarWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetTotalStat().MaxHp);
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHp());
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UPA_HpBarWidget::UpdateHpBar);

	}

	UMpBarWidget* MpBarWidget = Cast<UMpBarWidget>(InUserWidget);
	if (MpBarWidget)
	{
		MpBarWidget->SetMaxMp(Stat->MaxMp);
		MpBarWidget->UpdateMpBar(Stat->GetCurrentMp());
		Stat->OnMpChanged.AddUObject(MpBarWidget, &UMpBarWidget::UpdateMpBar);

	}

	UPA_ExpBarWidget* ExpBarWidget = Cast<UPA_ExpBarWidget>(InUserWidget);
	if (ExpBarWidget)
	{
		ExpBarWidget->SetMaxExp(Stat->GetTotalStat().MaxExp);
		ExpBarWidget->UpdateExpBar(Stat->GetCurrentExp());
		Stat->OnExpChanged.AddUObject(ExpBarWidget, &UPA_ExpBarWidget::UpdateExpBar);

	}
}

//void AddExp(float InIncreaseExp)
//{
//	Level
//
//	LevelMaxExp
//
//		if (CurExp + 50 < LevelMaxExp)
//		{
//			return;
//	}
//
//	NextCurExp = CurExp + 50 - LevelMaxExp;
//	Level++;
//
//	Updatestat(Level);
//}

//void Key1번입력()
//{
//	UPA_ItemData* SlotItemData = QuickSlotComp->FindSlotInfo(1);
//	if (SlotItemData == nullptr)
//	{
//		return;
//	}
//	//TakeItemActions[static_cast<uint8>(SlotItemData->Type)].ItemDelegate.ExecuteIfBound(SlotItemData);
//	if (IsholdingItem)
//	{
//		EquipWeapon(SlotItemData);
//	}
//	else
//	{
//		HoldWeapon(SlotItemData);
//	}
//}

void APA_CharacterBase::TakeItem(UPA_ItemData* InItemData)
{
	if (InItemData)
	{
		/*InventoryComp->AddItem(InItemDat);
		if (InItemData == 무기)
		{
			등뒤에 소켓에 장착
				Slot* SlotInfo = QuickSlotComp->FindEmptySlot()
				SlotInfo->SetItemData(InItemData);
			HoldWeapon(InItemData);
		}*/

		//TakeItemActions[static_cast<uint8>(InItemData->Type)].ItemDelegate.ExecuteIfBound(InItemData);
		EquipWeapon(InItemData);
	}
}

void APA_CharacterBase::EquipWeapon(UPA_ItemData* InItemData)
{
	UPA_WeaponItemData* WeaponItemData = Cast<UPA_WeaponItemData>(InItemData);

	if (WeaponItemData)
	{
		if (WeaponItemData->WeaponMesh.IsPending())
		{
			WeaponItemData->WeaponMesh.LoadSynchronous();
		}
		Weapon->SetSkeletalMesh(WeaponItemData->WeaponMesh.Get());
		Stat->SetModifierStat(WeaponItemData->ModifierStat);
	}
}

void APA_CharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);
	HpBar->SetHiddenInGame(true);
}

void APA_CharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}

