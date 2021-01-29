// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMPInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIMPInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IMPBASE_API IIMPInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMPBase|Interface|Interaction")
	void OnInteract();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMPBase|Interface|Interaction")
	void OnInteractStop();
};
