// IMP Project - Robert Lehmann 2020-2021


#include "IMPPickupBase.h"

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
}
