// IMP Project - Robert Lehmann 2020-2021


#include "IMPInventoryItemBase.h"
#include "IMPBase/Components/IMPInventoryComponent.h"

UIMPInventoryItemBase::UIMPInventoryItemBase()
{
	ItemID = TEXT("001");
	ItemName = FText::FromString("Enter a name");
	ItemDescription = FText::FromString("Enter an item description");
	ItemValue = 0;
	ItemStack = 1;
	ItemStackSize = 1;
}

void UIMPInventoryItemBase::SetOwner(UIMPInventoryComponent* NewOwner)
{
	Owner = NewOwner;
}

void UIMPInventoryItemBase::SetWorld(UWorld* NewWorld)
{
	World = NewWorld;
}

void UIMPInventoryItemBase::MarkForDestruction()
{
	SetOwner(nullptr);
	SetWorld(nullptr);
	//MarkPendingKill();
}

#if WITH_EDITOR
void UIMPInventoryItemBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ItemStack = FMath::Clamp(ItemStack, 1, ItemStackSize);
}
#endif