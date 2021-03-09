// IMP Project - Robert Lehmann 2020-2021


#include "IMPPickupInteractable.h"
#include "IMPBase/IMPBase.h"

AIMPPickupInteractable::AIMPPickupInteractable()
{
	Mesh->SetCollisionProfileName("BlockAllDynamic");
}

void AIMPPickupInteractable::OnInteract_Implementation(APawn* Caller)
{
	OnPickUp();
}
