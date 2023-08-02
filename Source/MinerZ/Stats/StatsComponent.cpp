#include "StatsComponent.h"

#include "MinerZ/Core/ErrorDefine.h"

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (const FStatData& stat : m_baseStats)
	{
		auto newStatLine = NewObject<UStatLine>();
		newStatLine->InitializeFromData(stat);
		m_baseStatsLines.Add(newStatLine);
	}

	ReComputeStats();
}

FGuid UStatsComponent::AddDynamicStat(UStatLine* StatLine)
{
	FGuid newId = FGuid::NewGuid();
	m_dynamicStats[newId] = StatLine;
	
	ReComputeStats();

	return newId;
}

bool UStatsComponent::RemoveDynamicStat(FGuid StatId)
{
	int32 removedEntry = m_dynamicStats.Remove(StatId);

	return removedEntry != 1;
}

UStatLine* UStatsComponent::GetStatLine(FGameplayTag StatType) const
{
	for (const auto stat : m_computedActiveStats)
	{
		if(stat->GetGameplayTag() == StatType)
		{
			return stat;
		}
	}

	return nullptr;
}

float UStatsComponent::GetStatLineValue(const FGameplayTag& StatType) const
{
	UStatLine* statLine = GetStatLine(StatType);
	if(statLine == nullptr)
	{
		CORE_LOGM(LogTemp, "No Valid stat line found for type %s. Will return -1.", *StatType.ToString());
		return -1;
	}
	return statLine->GetValue();
}

float UStatsComponent::ApplyStatLineToValue(float value, const FGameplayTag& StatType) const
{
	UStatLine* statLine = GetStatLine(StatType);
	if(statLine == nullptr)
	{
		CORE_LOGM(LogTemp, "No Valid stat line found for type %s. Will return -1.", *StatType.ToString());
		return -1;
	}

	// TODO: This needs to take  into account if it's a positive or negative modifier (boost/res)
	float returnValue = 0;
	auto modifierType = statLine->GetLineModifierType();
	switch (modifierType)
	{
		case EStatLineType::Flat:
			returnValue = statLine->GetValue(); // simple flat value addition
			break;
		case EStatLineType::Percentage:
			returnValue = value * statLine->GetValue(); // 10 damage + 10% of 10 = 11 total-> We return the diff so 1
			break;
		default:
			CORE_LOGM(LogTemp, "Invalid modifier type enter for this line %s", *StatType.ToString());
	}

	return returnValue;
}

void UStatsComponent::ReComputeStats()
{
	// Clear the currents one
	m_computedActiveStats.Empty();

	//  Add all the base stats first
	auto addStatToExisting = [this](UStatLine* statLine)
	{
		for (UStatLine* stat : m_computedActiveStats)
		{
			if(stat->GetGameplayTag() == statLine->GetGameplayTag())
			{
				// Add the new line value on top of the existing one
				stat->ModifyValue(statLine->GetValue());
				return;
			}
		}

		// Add the new line if we didn't find any existing stats with this tag
		m_computedActiveStats.Add(statLine);
	};
	
	for (UStatLine* statLine : m_baseStatsLines)
	{
		addStatToExisting(statLine);
	}

	// Add the dynamic next
	for (TTuple<FGuid, UStatLine*> statEntry : m_dynamicStats)
	{
		UStatLine* statLine = statEntry.Value;
		addStatToExisting(statLine);
	}
}
