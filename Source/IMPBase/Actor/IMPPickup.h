// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPPickupBase.h"
#include "IMPPickup.generated.h"

/** An "arcade-like" pickup that the player can collect by colliding with its PickupTrigger */
UCLASS()
class IMPBASE_API AIMPPickup : public AIMPPickupBase
{
	GENERATED_BODY()

public:

	AIMPPickup();

	UPROPERTY(EditAnywhere)
	/* Triggering volume for actors to collide with to trigger the pickup */
	class UBoxComponent* PickupTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Interaction|Pickup")
	/* Only these Actors will be able to collect this Pickup */
	TArray<TSubclassOf<AActor>> AllowedActors;

private:

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
