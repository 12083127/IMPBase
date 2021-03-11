// IMP Project - Robert Lehmann 2020-2021


#include "IMPPickupBase.h"
#include "Components/AudioComponent.h"

AIMPPickupBase::AIMPPickupBase()
{
	Mesh->SetCollisionProfileName("NoCollision");

	bDestroyOnPickup = true;
}

void AIMPPickupBase::OnPickUp_Implementation()
{
	if (bDestroyOnPickup)
	{
		Destroy();
	}

	if (AudioComponent)
	{
		if (AudioComponent->IsPlaying())
		{
			return;
		}
	}

	PlayInteractionSound(ActivateSound);
}

//void AIMPPickupBase::OnInteract_Implementation(APawn* Caller)
//{
//}
