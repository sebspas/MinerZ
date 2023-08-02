#pragma once
#include "StatLine.h"
#include "MinerZ/Damage/DamagePayload.h"

#include "StatsComponent.generated.h"

UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	FGuid AddDynamicStat(UStatLine* StatLine);

	UFUNCTION(BlueprintCallable)
	bool RemoveDynamicStat(FGuid StatId);

	UFUNCTION(BlueprintCallable)
	UStatLine* GetStatLine(FGameplayTag StatType) const;

	UFUNCTION(BlueprintCallable)
	float GetStatLineValue(const FGameplayTag& StatType) const;
	
	UFUNCTION(BlueprintCallable)
	float ApplyStatLineToValue(float value, const FGameplayTag& StatType) const;

private:
	void ReComputeStats();
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<FStatData> m_baseStats;
	
	UPROPERTY()
	TArray<UStatLine*> m_baseStatsLines;

	UPROPERTY()
	TMap<FGuid, UStatLine*> m_dynamicStats;

	UPROPERTY()
	TArray<UStatLine*> m_computedActiveStats;
};
