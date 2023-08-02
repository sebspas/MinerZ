#pragma once

#include "Damage.h"

#include "DamagePayload.generated.h"

USTRUCT(BlueprintType)
struct FDamagePayload
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Source;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDamage> Damages;
};
