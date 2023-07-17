#pragma once
#include "Engine/DataTable.h"

USTRUCT(BlueprintType)
struct FStatDataTableEntry : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon {};
};
