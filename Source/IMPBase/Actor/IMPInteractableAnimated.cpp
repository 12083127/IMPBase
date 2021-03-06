// IMP Project - Robert Lehmann 2020-2021


#include "IMPInteractableAnimated.h"

AIMPInteractableAnimated::AIMPInteractableAnimated()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AIMPInteractableAnimated::SetInFocus(const bool bInFocus)
{
	Super::SetInFocus(bInFocus);

	Mesh->SetRenderCustomDepth(bInFocus);
}
