// IMP Project - Robert Lehmann 2020-2021


#include "IMPEquipmentComponent.h"

// Sets default values for this component's properties
UIMPEquipmentComponent::UIMPEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	StartupEquipment.Init(nullptr, StaticCast<int32>(EEquipmentSlot::LENGTH));
	Equipment.Init(nullptr, StaticCast<int32>(EEquipmentSlot::LENGTH));
}

// Called when the game starts
void UIMPEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	for (UIMPEquipmentItemBase* Item : StartupEquipment)
	{
		EquipItem(Item);
	}
}

UIMPEquipmentItemBase* UIMPEquipmentComponent::EquipItem(UIMPEquipmentItemBase* const Item)
{
	if (Item)
	{
		int32 SlotIndex = GetSlotIndex(Item->ItemSlotType);
		UIMPEquipmentItemBase* OutItem = Equipment[SlotIndex];

		Equipment[SlotIndex] = Item;

		return OutItem;
	}

	return nullptr;
}

UIMPEquipmentItemBase* UIMPEquipmentComponent::UnequipItem(const EEquipmentSlot InSlot)
{
	int32 SlotIndex = GetSlotIndex(InSlot);
	UIMPEquipmentItemBase* OutItem = Equipment[SlotIndex];

	Equipment[SlotIndex] = nullptr;

	return OutItem;
}

int32 UIMPEquipmentComponent::GetSlotIndex(const EEquipmentSlot Slot) const
{
	// hacky fix since I can't garantuee the there are not more slots than enum entries.
	if ((int32)Slot <= (int32)EEquipmentSlot::LENGTH)
	{
		return StaticCast<int32>(Slot);
	}
	else
		return 0;
}
