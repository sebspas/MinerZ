#pragma once
#include "GameplayTagContainer.h"
#include "Data/StatDataTableEntry.h"
#include "Engine/DataTable.h"

#include "StatLine.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStatChanged, float, OldValue, float, NewValue, float, Delta);

enum class EStatLineType : uint8
{
	Flat,
	Percentage
};

UCLASS(Blueprintable)
class UStatLine : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	const FGameplayTag& GetGameplayTag() const { return m_gameplayTag; }

	UFUNCTION(BlueprintCallable)
	const FStatDataTableEntry* GetStatLineDetails() const;

	UFUNCTION(BlueprintCallable)
	void ModifyValue(float modifier);

	UFUNCTION(BlueprintCallable)
	float GetValue() const { return m_base; }

	UFUNCTION(BlueprintCallable)
	const EStatLineType& GetLineModifierType() const { return m_lineType; }
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	FGameplayTag m_gameplayTag {FGameplayTag::EmptyTag};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	float m_base {1.f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	EStatLineType m_lineType {EStatLineType::Flat};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stat")
	FDataTableRowHandle m_statDataTableEntry {};

	UPROPERTY(BlueprintAssignable, Category="Stat")
	FOnStatChanged OnStatValueChanged;
};
