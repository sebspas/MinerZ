#pragma once
#include "StatLine.h"
#include "MinerZ/Damage/DamagePayload.h"

#include "StatsComponent.generated.h"

UCLASS()
class UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FGuid AddDynamicStat(const UStatLine* StatLine);

	UFUNCTION(BlueprintCallable)
	bool RemoveDynamicStat(FGuid StatId);

	UFUNCTION(BlueprintCallable)
	UStatLine* GetStatLine(const FGameplayTag& StatType) const;

	UFUNCTION(BlueprintCallable)
	float GetStatLineValue(const FGameplayTag& StatType) const;
	
	UFUNCTION(BlueprintCallable)
	float ApplyStatLineToValue(float value, const FGameplayTag& StatType) const;

private:
	void ReComputeStats();
	
protected:
	UPROPERTY()
	TArray<UStatLine> m_baseStats;

	UPROPERTY()
	TMap<FGuid, const UStatLine*> m_dynamicStats;

	UPROPERTY()
	TArray<UStatLine> m_computedActiveStats;
};
