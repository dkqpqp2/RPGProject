#pragma once

#include "../GameInfo.h"
#include "Engine/DataTable.h"
#include "S_Slot.generated.h"


USTRUCT(BlueprintType)
struct FS_Slot : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Amount;

};