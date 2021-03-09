// IMP Project - Robert Lehmann 2020-2021


#include "IMPInteractableStatic.h"
#include "IMPBase/IMPBase.h"
#include "Components/AudioComponent.h"

AIMPInteractableStatic::AIMPInteractableStatic() 
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToChannel(ECC_Focusable, ECollisionResponse::ECR_Block);
}

void AIMPInteractableStatic::BeginPlay()
{
	Super::BeginPlay();

}

void AIMPInteractableStatic::OnInteract_Implementation(APawn* Caller)
{
	if (AudioComponent)
	{
		if (AudioComponent->IsPlaying())
		{
			return;
		}
	}

	PlayInteractionSound(ActivateSound);
}

void AIMPInteractableStatic::SetInFocus(const bool bInFocus)
{
	Super::SetInFocus(bInFocus);

	Mesh->SetRenderCustomDepth(bInFocus);
}

