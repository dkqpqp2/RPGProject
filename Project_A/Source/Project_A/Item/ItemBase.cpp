// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Inventory/ItemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/PA_Collision.h"

// Sets default values
AItemBase::AItemBase()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	BoxMesh->SetupAttachment(Trigger);
	Widget->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_PATRIGGER);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 32.0f));
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Construction_VOL1/Meshes/SM_Boxes_03a.SM_Boxes_03a'"));
	if(BoxMeshRef.Object)
	{
		BoxMesh->SetStaticMesh(BoxMeshRef.Object);
	}
	BoxMesh->SetRelativeLocation(FVector(0.0f, -5.0f, -32.0f));
	BoxMesh->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetRef(TEXT("/Game/Project_A/Item/WBP_Item.WBP_Item_C"));
	if (WidgetRef.Class)
	{
		Widget->SetWidgetClass(WidgetRef.Class);
	}
	Widget->SetRelativeLocation(FVector(0.0f, -5.0f, 5.0f));
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	//Widget->SetVisibility(false);

	ItemComponent = CreateDefaultSubobject<UItemComponent>(TEXT("ItmeComponent"));
}

void AItemBase::FClickAction()
{
	/*Effect->SetActive(true);
	BoxMesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->OnSystemFinished.AddDynamic(this, &AItemBase::OnEffectFinished);*/
}

void AItemBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	


}

void AItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//Widget->SetVisibility(true);
}

void AItemBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Widget->SetVisibility(false);
}

void AItemBase::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	//Destroy();
}



