// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMPInventoryItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIMPInventoryItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IMPBASE_API IIMPInventoryItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnUse();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DestroyItem();
};
