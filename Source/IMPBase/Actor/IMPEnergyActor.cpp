// IMP Project - Robert Lehmann 2020-2021


#include "IMPEnergyActor.h"
#include "Components/BoxComponent.h"
#include "IMPBase/Components/IMPEnergyComponent.h"

AIMPEnergyActor::AIMPEnergyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionTriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("InteractonTriggerVolume")));
	InteractionTriggerVolume->SetupAttachment(RootComponent);

	EnergyComponent = CreateDefaultSubobject<UIMPEnergyComponent>(FName(TEXT("EnergyComponent")));

	bEmptyEventDone = false;
	bChargedEventDone = false;
}

void AIMPEnergyActor::BeginPlay()
{
	Super::BeginPlay();
}

void AIMPEnergyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnergyComponent->IsEnergyContainer())
	{
		bool bCharged = EnergyComponent->IsCharged();

		if (bCharged && !bChargedEventDone)
		{
			bChargedEventDone = true;
			OnChargedEvent();
		}

		return;
	}
	else
	{
		bool bDrained = EnergyComponent->IsDrained();

		if (bDrained && !bEmptyEventDone)
		{
			bEmptyEventDone = true;
			OnDrainedEvent();
		}

		return;
	}
}

void AIMPEnergyActor::OnDrainedEvent_Implementation()
{
}

void AIMPEnergyActor::OnChargedEvent_Implementation()
{
}
