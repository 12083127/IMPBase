// IMP Project - Robert Lehmann 2020-2021


#include "IMPPickupInteractable.h"

AIMPPickupInteractable::AIMPPickupInteractable()
{
	Mesh->SetCollisionProfileName("BlockAllDynamic");
}

void AIMPPickupInteractable::OnInteract_Implementation()
{
	Super::OnInteract_Implementation();
	OnPickUp();
}
