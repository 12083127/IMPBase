// IMP Project - Robert Lehmann 2020-2021


#include "IMPInteractableBase.h"
#include "Kismet/GameplayStatics.h"
#include "IMPBase/IMPBase.h"

// Sets default values
AIMPInteractableBase::AIMPInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DisplayName = FText::FromString("Interactable");
}

// Called when the game starts or when spawned
void AIMPInteractableBase::BeginPlay()
{
	Super::BeginPlay();
}

bool AIMPInteractableBase::PlayInteractionSound(USoundBase* const Sound)
{
	if (Sound)
	{
		AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, Sound, GetActorLocation());
		return true;
	}

	return false;
}

void AIMPInteractableBase::SetInFocus(const bool bInFocus){}

void AIMPInteractableBase::OnInteract_Implementation(APawn* Caller){}
