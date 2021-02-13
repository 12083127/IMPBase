// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "IMPBase/IMPBase.h"
#include "IMPGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class IMPBASE_API UIMPGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UIMPGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "IMP Base|Ability")
	EIMPAbilityInputID AbilityInputID;
};
