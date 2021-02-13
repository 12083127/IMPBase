// IMP Project - Robert Lehmann 2020-2021

#include "IMPEnergyComponent.h"

#include "IMPBase/AI/IMPNPCCharacterBase.h"

// Sets default values for this component's properties
UIMPEnergyComponent::UIMPEnergyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	EnergyType = EEnergyType::ET_Fire;

	EnergyMax = 100.f;
	Energy = 100.f;

	bCharged = false;
	bChargeable = false;
	bDrained = false;
	bDrainable = false;
	bContainer = false;
}

// Called when the game starts
void UIMPEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	EnergyLevel.Initialize(EnergyMax, Energy);
}

// Called every frame
void UIMPEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bContainer)
	{
		bDrained = false;
		bDrainable = false;

		bCharged = EnergyLevel.Current == EnergyLevel.Max;

		if (bCharged)
		{
			bChargeable = false;
			return;
		}
		else
		{
			bChargeable = true;
			return;
		}
	}
	else
	{
		bCharged = false;
		bChargeable = false;

		bDrained = EnergyLevel.Current <= 0;

		if (bDrained)
		{
			bDrainable = false;
			return;
		}
		else
		{
			AIMPNPCCharacterBase* NPC = Cast<AIMPNPCCharacterBase>(GetOwner());

			if (NPC)
			{
				if (NPC->IsDead())
				{
					bDrainable = true;
					return;
				}
				else
				{
					bDrainable = false;
					return;
				}
			}
			else
			{
				bDrainable = true;
				return;
			}
		}
	}
}

void UIMPEnergyComponent::ModifyEnergyMax(const float ByAmount)
{
	EnergyLevel.Max += ByAmount;
}

void UIMPEnergyComponent::SetEnergyMax(const float InValue)
{
	EnergyLevel.Max = InValue;
}

void UIMPEnergyComponent::ModifyCurrentEnergyLevel(const float ByAmount)
{
	EnergyLevel.Modify(ByAmount);
}

void UIMPEnergyComponent::SetCurrentEnergyLevel(const float InValue)
{
	EnergyLevel.Set(InValue);
}

void UIMPEnergyComponent::SetEnergyType(const EEnergyType InType)
{
	EnergyType = InType;
}

