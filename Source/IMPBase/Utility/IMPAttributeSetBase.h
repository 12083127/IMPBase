// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "IMPBase/Components/IMPAbilitySystemComponent.h"
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

	UPROPERTY(BlueprintReadOnly, Category = "IMPBase|Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, Health);

	UPROPERTY(BlueprintReadOnly, Category = "IMPBase|Attributes")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, HealthMax);

	UPROPERTY(BlueprintReadOnly, Category = "IMPBase|Attributes")
	FGameplayAttributeData DrainRate;
	ATTRIBUTE_ACCESSORS(UIMPAttributeSetBase, DrainRate);
};
