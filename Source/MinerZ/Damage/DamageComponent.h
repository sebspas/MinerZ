#pragma once

#include "DamagePayload.h"
#include "Data/DamageDataTableEntry.h"

#include "DamageComponent.generated.h"

UCLASS(ClassGroup=Damage, BlueprintType, meta=(BlueprintSpawnableComponent))
class UDamageComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(FDamagePayload DamagePayload);

private:
	void ApplyBoostToDamage(FDamagePayload& DamagePayload) const;
	void ApplyResistanceToDamage(FDamagePayload& DamagePayload) const;

	const FDamageDataTableEntry* GetDamageTableEntryForType(const FGameplayTag& DamageType) const;

protected:
	// Damage data table to fetch what stats boots/nerf a specific damage type
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	UDataTable* m_damageDataTable {};
};
