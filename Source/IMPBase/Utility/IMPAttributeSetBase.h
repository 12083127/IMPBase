// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "IMPAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class IMPBASE_API UIMPAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UIMPAttributeSetBase();

	UPROPERTY(BlueprintReadOnly, Category = "IMP Base|Attributes")
	/** Current Health Value. NOTE: Make sure to set HealthMax first since Health is being clamped to HealthMax!*/
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, Health);

	UPROPERTY(BlueprintReadOnly, Category = "IMP Base|Attributes")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, HealthMax);

	UPROPERTY(BlueprintReadOnly, Category = "IMP Base|Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "IMP Base|Attributes")
	FGameplayAttributeData StaminaMax;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, StaminaMax);

	UPROPERTY(BlueprintReadOnly, Category = "IMP Base|Attributes")
	FGameplayAttributeData DrainRate;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, DrainRate);

	// NOTE: should mainly be used for clamping values pre value change. For other actions triggered by attribute change use the predefined delegates
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
