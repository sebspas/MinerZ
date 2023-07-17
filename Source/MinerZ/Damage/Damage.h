#pragma once

#include "GameplayTagContainer.h"
#include "Data/DamageDataTableEntry.h"
#include "Engine/DataTable.h"

#include "Damage.generated.h"

UCLASS(BlueprintType)
class UDamage : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	float GetDamageValue() const { return m_baseDamageValue; }

	UFUNCTION(BlueprintCallable)
	const FGameplayTag& GetDamageType() const { return m_damageTypeTag; } 
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	FGameplayTag m_damageTypeTag {FGameplayTag::EmptyTag};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	float m_baseDamageValue {1.f};
};