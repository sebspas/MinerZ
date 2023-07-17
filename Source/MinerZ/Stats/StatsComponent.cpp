#include "StatsComponent.h"

#include "MinerZ/Core/ErrorDefine.h"

FGuid UStatsComponent::AddDynamicStat(const UStatLine* StatLine)
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

UStatLine* UStatsComponent::GetStatLine(const FGameplayTag& StatType) const
{
	auto foundElement = m_dynamicStats.FindByPredicate([&StatType](const UStatLine& line)
	{
		return line.GetGameplayTag() == StatType;
	});

	return foundElement;
}

float UStatsComponent::GetStatLineValue(const FGameplayTag& StatType) const
{
	UStatLine* statLine = GetStatLine(StatType);
	if(statLine == nullptr)
	{
		CORE_LOG(LogTemp, TEXT("No Valid stat line found for type %s. Will return -1."), StatType.ToString());
		return -1;
	}
	return statLine->GetValue();
}

float UStatsComponent::ApplyStatLineToValue(float value, const FGameplayTag& StatType) const
{
	UStatLine* statLine = GetStatLine(StatType);
	if(statLine == nullptr)
	{
		CORE_LOG(LogTemp, TEXT("No Valid stat line found for type %s. Will return -1."), StatType.ToString());
		return -1;
	}

	// TODO: This needs to take  into account if it's a positive or negative modifier (boost/res)
	float returnValue = 0;
	auto modifierType = statLine->GetLineModifierType();
	switch (modifierType)
	{
		case EStatLineType::Flat:
			returnValue = value + statLine->GetValue(); // simple flat value addition
			break;
		case EStatLineType::Percentage:
			returnValue = value + value * statLine->GetValue(); // 10 damage + 10% of 10 = 11 total 
			break;
		default:
			CORE_LOG(LogTemp, TEXT("Invalid modifier type enter for this line %s"), StatType.ToString());
	}

	return returnValue;
}

void UStatsComponent::ReComputeStats()
{
	
}
