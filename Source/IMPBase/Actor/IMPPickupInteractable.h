// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPPickupBase.h"
#include "IMPPickupInteractable.generated.h"

/** This Pickup variant can only be picked up if the player interacts with it */
UCLASS()
class IMPBASE_API AIMPPickupInteractable : public AIMPPickupBase
{
	GENERATED_BODY()
		
public:

	AIMPPickupInteractable();

	virtual void OnInteract_Implementation() override;
};
