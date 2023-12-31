﻿#include "DamageComponent.h"

#include "MinerZ/Core/ErrorDefine.h"
#include "MinerZ/Stats/StatsComponent.h"
#include "MinerZ/Stats/Data/StatsTypes.h"

void UDamageComponent::TakeDamage(FDamagePayload DamagePayload)
{
	// Resolve bonus (ex. physical boost, fire boost, ...)
	ApplyBoostToDamage(DamagePayload);

	// Grab the StatsComponent of the target
	UStatsComponent* targetStatComponent = GetOwner()->GetComponentByClass<UStatsComponent>();
	if(!IsValid(targetStatComponent))
	{
		CORE_LOG(LogTemp, TEXT("The target doesn't have a valid sourceStatComponent. Potential resistance on damage won't be applied."));
		return;
	}

	// Resolve resistance (ex. armor, elemental res, ...)
	ApplyResistanceToDamage(DamagePayload);

	// Apply the damage to the health of the target
	if(UStatLine* statLine = targetStatComponent->GetStatLine(STATS_Health))
	{
		for (const FDamage& damage : DamagePayload.Damages)
		{
			statLine->ModifyValue(-damage.BaseDamageValue);
		}
	}
	else
	{
		CORE_LOGM(LogTemp, "Couldn't find stats for tag: %s", *STATS_Health.GetTag().ToString());
	}
	

}

void UDamageComponent::ApplyBoostToDamage(FDamagePayload& DamagePayload) const
{
	// Grab the StatsComponent of the source
	UStatsComponent* sourceStatComponent = DamagePayload.Source->GetComponentByClass<UStatsComponent>();
	if(!IsValid(sourceStatComponent))
	{
		CORE_LOG(LogTemp, TEXT("The source doesn't have a valid sourceStatComponent. Potential bonuses on damage won't be applied."));
		return;
	}

	for (const FDamage& damage : DamagePayload.Damages)
	{
		const FDamageDataTableEntry* damageEntryForType = GetDamageTableEntryForType(damage.DamageTypeTag);
		if(damageEntryForType == nullptr)
		{
			CORE_LOGM(LogTemp, "No row was found for this damage type %s.", *damage.DamageTypeTag.ToString());
			break;
		}

		float newFinalValue = 0.f;
		for (const FGameplayTag& statTag : damageEntryForType->BoostedByStats)
		{
			newFinalValue += sourceStatComponent->ApplyStatLineToValue(damage.BaseDamageValue, statTag);
		}
	}
}

void UDamageComponent::ApplyResistanceToDamage(FDamagePayload& DamagePayload) const
{
	// TODO : needs to apply the res part
}

const FDamageDataTableEntry* UDamageComponent::GetDamageTableEntryForType(const FGameplayTag& DamageType) const
{
	if(IsValid(m_damageDataTable))
	{
		CORE_LOG(LogTemp, TEXT("Invalid data table set for damages."));
		return nullptr;
	}

	TArray<FDamageDataTableEntry*> rows;
	m_damageDataTable->GetAllRows("UDamageComponent::GetDamageTableEntry", rows);
	for (const FDamageDataTableEntry* row : rows)
	{
		if(row->DamageType == DamageType)
		{
			return row;
		}
	}
	
	return nullptr;
}
