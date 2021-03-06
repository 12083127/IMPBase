// IMP Project - Robert Lehmann 2020-2021


#include "IMPInteractableStatic.h"

AIMPInteractableStatic::AIMPInteractableStatic() 
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AIMPInteractableStatic::SetInFocus(const bool bInFocus)
{
	Super::SetInFocus(bInFocus);

	Mesh->SetRenderCustomDepth(bInFocus);
}
