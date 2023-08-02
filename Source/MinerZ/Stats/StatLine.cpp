#include "StatLine.h"

#include "MinerZ/Core/ErrorDefine.h"

void UStatLine::InitializeFromData(FStatData StatData)
{
	m_statBaseData = StatData;
	m_current = m_statBaseData.Base;
}

FStatDataTableEntry UStatLine::GetStatLineDetails() const
{
	if(m_statBaseData.StatDataTableEntry.IsNull())
	{
		CORE_LOG(LogTemp, TEXT("Invalid data table set for this stat line."));
		return FStatDataTableEntry{};
	}

	return *m_statBaseData.StatDataTableEntry.GetRow<FStatDataTableEntry>("UStatLine::GetStatLineDetails");
}

void UStatLine::ModifyValue(float modifier)
{
	float oldValue = m_statBaseData.Base;

	m_current += modifier;
	
	OnStatValueChanged.Broadcast(oldValue, m_current, modifier);
}
