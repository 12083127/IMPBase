// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPContainerBase.generated.h"

/**
 * 
 */
UCLASS()
class IMPBASE_API AIMPContainerBase : public AIMPInteractableBase
{
	GENERATED_BODY()

public:

	AIMPContainerBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UIMPInventoryComponent* Inventory;

protected:

private:

};
