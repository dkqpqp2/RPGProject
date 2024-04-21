// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Interface/PA_AnimationAttackInterface.h"
#include "Interface/PA_CharacterWidgetInterface.h"
#include "Interface/PA_CharacterItemInterface.h"
#include "PA_CharacterBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPACharacter, Log, All);

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater,
};

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UPA_ItemData* /*InItemData*/)
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}
	FOnTakeItemDelegate ItemDelegate;
};

UCLASS()
class PROJECT_A_API APA_CharacterBase : public ACharacter, public IPA_AnimationAttackInterface, public IPA_CharacterWidgetInterface, public IPA_CharacterItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APA_CharacterBase();
	
	virtual void PostInitializeComponents() override;

	const UPA_CharacterStatComponent* GetStatComponent() const;
protected:
	virtual void SetCharacterControlData(const class UPA_CharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UPA_CharacterControlData*> CharacterControlManager;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPA_ComboActionData> ComboActionData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	void ProcessComboCommand();
	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;
	bool AddWeapon = false;

protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual void SetDead();
	void PlayDeadAnimation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneCaptureComponent2D> FaceCapture;

	UPROPERTY(EditAnywhere, Category = Inventory)
	TObjectPtr<class UPA_PlayerInventorySystem> Inventory;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPA_CharacterStatComponent> Stat;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPA_WidgetComponent> HpBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> ExpBar;

	virtual void SetupCharacterWidget(class UPA_UserWidget* InUserWidget) override;

protected:
	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;

	virtual void TakeItem(UPA_ItemData* InItemData) override;
	virtual void EquipWeapon(class UPA_ItemData* InItemData);
};
