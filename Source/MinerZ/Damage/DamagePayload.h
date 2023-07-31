#pragma once

#include "Damage.h"

#include "DamagePayload.generated.h"

UCLASS(BlueprintType)
class UDamagePayload : public UObject
{
	GENERATED_BODY()
	
public:
	AActor* GetSource() const { return m_source; }
	
	TArray<UDamage*>& GetDamages() { return m_damages; }
	
private:
	UPROPERTY()
	AActor* m_source;
	
	UPROPERTY()
	TArray<UDamage*> m_damages;
};
