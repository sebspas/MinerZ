#pragma once
#include "DamagePayload.h"

UCLASS()
class UDamageComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(UDamagePayload& DamagePayload);

private:
	void ApplyBoostToDamage(UDamagePayload& DamagePayload) const;
	void ApplyResistanceToDamage(UDamagePayload& DamagePayload) const;

	const FDamageDataTableEntry* GetDamageTableEntryForType(const FGameplayTag& DamageType) const;

protected:
	// Damage data table to fetch what stats boots/nerf a specific damage type
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	UDataTable* m_damageDataTable {};
};
