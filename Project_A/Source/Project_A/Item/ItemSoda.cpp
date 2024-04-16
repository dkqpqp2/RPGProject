// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSoda.h"
#include "Components/StaticMeshComponent.h"

AItemSoda::AItemSoda()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SodaMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Project_A/Assets/Soda/Soda_Can.Soda_Can'"));
	if (SodaMeshRef.Object)
	{
		BoxMesh->SetStaticMesh(SodaMeshRef.Object);

		static ConstructorHelpers::FObjectFinder<UMaterialInterface> SodaMaterialRef(TEXT("/Script/Engine.Material'/Game/Project_A/Assets/Soda/MT_Soda.MT_Soda'"));
		if (SodaMaterialRef.Object)
		{
			BoxMesh->SetMaterial(0, SodaMaterialRef.Object);
		}

		static ConstructorHelpers::FObjectFinder<UStaticMesh> SodaCapMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Project_A/Assets/Soda/Soda_Can_Cap.Soda_Can_Cap'"));
		if (SodaCapMeshRef.Object)
		{
			Cap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap"));
			Cap->SetupAttachment(BoxMesh);
			Cap->SetStaticMesh(SodaCapMeshRef.Object);
		}

		static ConstructorHelpers::FObjectFinder<UStaticMesh> SodaOpenerMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Project_A/Assets/Soda/Soda_Can_Opener.Soda_Can_Opener'"));
		if (SodaOpenerMeshRef.Object)
		{
			Opener = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Opener"));
			Opener->SetupAttachment(BoxMesh);
			Opener->SetStaticMesh(SodaOpenerMeshRef.Object);
		}
		BoxMesh->SetRelativeLocation(FVector(0.0f, -5.0f, 0.0f));
		BoxMesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
		Cap->SetCollisionProfileName(TEXT("NoCollision"));
		Opener->SetCollisionProfileName(TEXT("NoCollision"));
	}
	BoxMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

