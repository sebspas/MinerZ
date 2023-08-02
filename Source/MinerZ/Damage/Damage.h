#pragma once

#include "GameplayTagContainer.h"

#include "Damage.generated.h"

USTRUCT(BlueprintType)
struct FDamage
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	FGameplayTag DamageTypeTag {FGameplayTag::EmptyTag};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	float BaseDamageValue {1.f};
};