// IMP Project - Robert Lehmann 2020-2021

#include "IMPAttributeSetBase.h"

UIMPAttributeSetBase::UIMPAttributeSetBase()
{
}

void UIMPAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, HealthMax.GetCurrentValue());
	}

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, StaminaMax.GetCurrentValue());
	}
}
