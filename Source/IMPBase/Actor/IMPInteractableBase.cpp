// IMP Project - Robert Lehmann 2020-2021


#include "IMPInteractableBase.h"
#include "IMPBase/IMPBase.h"

// Sets default values
AIMPInteractableBase::AIMPInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	bUseInteractionTimeSpan = false;
	InteractTimeSpan = 5.f;
}

// Called when the game starts or when spawned
void AIMPInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	bReadyToInteract = !bUseInteractionTimeSpan;
}

float AIMPInteractableBase::GetInteractionTimeNormalized() const
{
	if (InteractTimeSpan <= 0.f)
	{
		return 1.f;
	}
	else
	{
		return (GetWorldTimerManager().GetTimerElapsed(InteractTimerHandle) / InteractTimeSpan);
	}

	return 0.f;
}

void AIMPInteractableBase::SetReadyToInteract()
{
	bReadyToInteract = true;
	OnInteract_Implementation();
}

void AIMPInteractableBase::SetInFocus(const bool bInFocus)
{
	Mesh->SetRenderCustomDepth(bInFocus);
}

void AIMPInteractableBase::OnInteract_Implementation()
{
	if (!bReadyToInteract)
	{
		GetWorldTimerManager().SetTimer(InteractTimerHandle, this, &AIMPInteractableBase::SetReadyToInteract, InteractTimeSpan, false, InteractTimeSpan);
		return;
	}
	else
	{
		printc(1, FColor::Red, "Interacted!");
		ResetInteractionTimer();
	}
}

void AIMPInteractableBase::OnInteractStop_Implementation()
{
	if (bUseInteractionTimeSpan && GetWorldTimerManager().IsTimerActive(InteractTimerHandle))
	{
		ResetInteractionTimer();
	}
}

void AIMPInteractableBase::ResetInteractionTimer()
{
	GetWorldTimerManager().ClearTimer(InteractTimerHandle);
	bReadyToInteract = !bUseInteractionTimeSpan;
}
