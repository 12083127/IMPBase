// IMP Project - Robert Lehmann 2020-2021


#include "IMPInventoryItemBase.h"
#include "Components/Widget.h"
#include "IMPBase/Components/IMPInventoryComponent.h"
#include "IMPBase/IMPBase.h"

UIMPInventoryItemBase::UIMPInventoryItemBase()
{
	ItemID = TEXT("001");
	ItemName = FText::FromString("Enter a name");
	ItemDescription = FText::FromString("Enter an item description");
	ItemValue = 0;
	ItemStack = 1;
	ItemStackSize = 1;

	printf(FColor::Red, "Item created: %s", *GetName());

	ClearEntryWidget();
}

void UIMPInventoryItemBase::SetEntryWidget(UWidget* InWidget)
{
	CurrentEntryWidget = InWidget;
}

void UIMPInventoryItemBase::ClearEntryWidget()
{
	CurrentEntryWidget = nullptr;
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
	ClearEntryWidget();
	SetOwner(nullptr);
	SetWorld(nullptr);
	MarkPendingKill();
}

void UIMPInventoryItemBase::BeginDestroy()
{
	Super::BeginDestroy();

	logstring("%s: Item destroyed", *ItemName.ToString());
}

#if WITH_EDITOR
void UIMPInventoryItemBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ItemStack = FMath::Clamp(ItemStack, 1, ItemStackSize);
}
#endif