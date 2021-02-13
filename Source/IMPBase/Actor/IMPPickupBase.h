// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPPickupBase.generated.h"

/** Abstract base pickup class that every pickup inherits from */
UCLASS(Abstract)
class IMPBASE_API AIMPPickupBase : public AIMPInteractableBase
{
	GENERATED_BODY()

public:

	AIMPPickupBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Interaction|Pickup")
	/** Whether or not to destroy the Actor when the event OnPickup() fires */
	bool bDestroyOnPickup;

	UFUNCTION(BlueprintNativeEvent)
	/** OnPickUp Event handle that will destroy the pickup actor on default when called.
	  * Further behaviour can be defines inside blueprints by the designer.
	  */
	void OnPickUp();
	virtual void OnPickUp_Implementation();
};
