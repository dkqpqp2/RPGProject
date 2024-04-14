#pragma once

#include "../GameInfo.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "ItemData.h"
#include "S_Item.generated.h"


USTRUCT(BlueprintType)
struct FS_Item : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	ENewItemType ItemType;
};