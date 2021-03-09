// IMP Project - Robert Lehmann 2020-2021


#include "IMPInteractableAnimated.h"
#include "IMPBase/IMPBase.h"
#include "Components/SkeletalMeshComponent.h"

AIMPInteractableAnimated::AIMPInteractableAnimated()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToChannel(ECC_Focusable, ECollisionResponse::ECR_Block);

	bInteractableState = false;
}

void AIMPInteractableAnimated::SetInteractableState(const bool bState)
{
	bInteractableState = bState;
}

void AIMPInteractableAnimated::OnInteract_Implementation(APawn* Caller)
{
	if (Mesh->IsPlaying())
	{
		return;
	}

	bInteractableState = !bInteractableState;

	if (bInteractableState)
	{
		PlayInteractionSound(ActivateSound);
		PlayInteractionAnim(ActivateAnimation);
	}
	else	// check if deactivate sound and/or anim assets are set. If not, just play the activate sound and/or anim again.
	{
		if (PlayInteractionSound(DeactivateSound))
		{}
		else
		{
			PlayInteractionSound(ActivateSound);
		}

		if (PlayInteractionAnim(DeactivateAnimation))
		{}
		else
		{
			PlayInteractionAnim(ActivateAnimation);
		}
	}
}

void AIMPInteractableAnimated::SetInFocus(const bool bInFocus)
{
	Super::SetInFocus(bInFocus);

	Mesh->SetRenderCustomDepth(bInFocus);
}

bool AIMPInteractableAnimated::PlayInteractionAnim(UAnimationAsset* const Anim)
{
	if (Anim && Mesh)
	{
		Mesh->PlayAnimation(Anim, false);
		return true;
	}
	
	return false;
}
