#pragma once

#include "Damage.h"

UCLASS(BlueprintType)
class UDamagePayload : public UObject
{
	GENERATED_BODY()
	
public:
	AActor* GetSource() const { return m_source; }
	
	TArray<UDamage>& GetDamages() { return m_damages; }
	
private:
	UPROPERTY(BlueprintReadWrite)
	AActor* m_source;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UDamage> m_damages;
};
