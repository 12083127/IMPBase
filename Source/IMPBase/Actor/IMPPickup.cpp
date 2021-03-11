// IMP Project - Robert Lehmann 2020-2021


#include "IMPPickup.h"
#include "Components/BoxComponent.h"
#include "IMPBase/IMPBase.h"

AIMPPickup::AIMPPickup()
{
	PickupTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupTriggerVolume"));
	PickupTrigger->SetGenerateOverlapEvents(true);
	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &AIMPPickup::OnComponentBeginOverlap);
	PickupTrigger->SetupAttachment(RootComponent);
}

void AIMPPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIMPPickup* Self = Cast<AIMPPickup>(OtherActor);

	if (!Self && OtherActor != this)
	{
		for (TSubclassOf<AActor> Actor : AllowedActors)
		{
			if (OtherActor->IsA(Actor))
			{
				OnPickUp();
			}
		}
	}
}
