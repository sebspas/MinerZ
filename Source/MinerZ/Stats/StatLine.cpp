#include "StatLine.h"

#include "MinerZ/Core/ErrorDefine.h"

FStatDataTableEntry UStatLine::GetStatLineDetails() const
{
	if(m_statDataTableEntry.IsNull())
	{
		CORE_LOG(LogTemp, TEXT("Invalid data table set for this stat line."));
		return FStatDataTableEntry{};
	}

	return *m_statDataTableEntry.GetRow<FStatDataTableEntry>("UStatLine::GetStatLineDetails");
}

void UStatLine::ModifyValue(float modifier)
{
	float oldValue = m_base;

	m_base += modifier;
	
	OnStatValueChanged.Broadcast(oldValue, m_base, modifier);
}
