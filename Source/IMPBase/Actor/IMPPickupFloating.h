// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPPickup.h"
#include "IMPPickupFloating.generated.h"

/** An "arcade-like" pickup that will float up and down and rotate around its own Z-Axis.
 * This will be picked up, when the player walks into the Pickup Trigger.
 */
UCLASS(Blueprintable)
class IMPBASE_API AIMPPickupFloating : public AIMPPickup
{
	GENERATED_BODY()

public:

	AIMPPickupFloating();

	/* Speed per tick this Pickup will rotate around its Z-Axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMPBase")
	float RotationSpeed;

	/* The Z-Range this Pickup will float up and down */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMPBase")
	float ZBoppinRange;

	virtual void Tick(float DeltaTime) override;
};
