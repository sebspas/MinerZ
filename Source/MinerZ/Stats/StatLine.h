#pragma once
#include "GameplayTagContainer.h"
#include "Data/StatDataTableEntry.h"
#include "Engine/DataTable.h"

#include "StatLine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStatChanged, float, OldValue, float, NewValue, float, Delta);

UENUM()
enum class EStatLineType : uint8
{
	Flat,
	Percentage
};

USTRUCT()
struct FStatData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Stat")
	FGameplayTag GameplayTag {FGameplayTag::EmptyTag};
	
	UPROPERTY(EditAnywhere, Category="Stat")
	float Base {1.f};

	UPROPERTY(EditAnywhere, Category="Stat")
	EStatLineType LineType {EStatLineType::Flat};

	UPROPERTY(EditAnywhere, Category="Stat")
	FDataTableRowHandle StatDataTableEntry {};
};

UCLASS()
class UStatLine : public UObject
{
	GENERATED_BODY()

public:

	void InitializeFromData(FStatData StatData);
	
	UFUNCTION(BlueprintCallable)
	const FGameplayTag& GetGameplayTag() const { return m_statBaseData.GameplayTag; }

	UFUNCTION(BlueprintCallable)
	FStatDataTableEntry GetStatLineDetails() const;

	UFUNCTION(BlueprintCallable)
	void ModifyValue(float modifier);

	UFUNCTION(BlueprintCallable)
	float GetValue() const { return m_current; }

	UFUNCTION(BlueprintCallable)
	const EStatLineType& GetLineModifierType() const { return m_statBaseData.LineType; }
	
private:
	UPROPERTY(EditAnywhere, DisplayName="Stats Base Values")
	FStatData m_statBaseData;
	
	UPROPERTY(BlueprintAssignable, Category="Stat")
	FOnStatChanged OnStatValueChanged;
	
	float m_current {0.f};
};
