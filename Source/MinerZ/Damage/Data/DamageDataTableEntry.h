#pragma once
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"

#include "DamageDataTableEntry.generated.h"

USTRUCT(BlueprintType)
struct FDamageDataTableEntry : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DamageType {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon {};

	// List of the Gameplay Tags of Stats that are going to boost damage of this type
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> BoostedByStats;

	// List of the Gameplay Tags of Stats that are going to reduce damage of this type
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> ReducedByStats;
};
