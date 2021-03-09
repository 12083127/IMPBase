// IMP Project - Robert Lehmann 2020-2021


#include "IMPContainerStatic.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "IMPBase/IMPBase.h"
#include "IMPBase/Player/IMPPlayerController.h"
#include "IMPBase/UI/IMPHUD.h"

AIMPContainerStatic::AIMPContainerStatic()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToChannel(ECC_Focusable, ECollisionResponse::ECR_Block);
}

void AIMPContainerStatic::OnInteract_Implementation(APawn* Caller)
{
	// this will currently soft-lock the interact event due to the sound playing during pause never finishes.
	// further reasearch needed to fix
	//if (AudioComponent)
	//{
	//	if (AudioComponent->IsPlaying())
	//	{
	//		return;
	//	}
	//}

	PlayInteractionSound(ActivateSound);

	AIMPPlayerController* PC = Cast<AIMPPlayerController>(Caller->Controller);

	if (PC)
	{
		UUserWidget* ContainerScreen = PC->GetContainerScreen();

		if (ContainerScreen)
		{
			if (ContainerScreen->IsVisible())
			{
				PC->HideContainerScreen();
			}
			else
			{
				PC->ShowContainerScreen(this);
			}
		}
		else
		{
			PC->ShowContainerScreen(this);
		}
	}
}

void AIMPContainerStatic::SetInFocus(const bool bInFocus)
{
	Super::SetInFocus(bInFocus);

	Mesh->SetRenderCustomDepth(bInFocus);
}