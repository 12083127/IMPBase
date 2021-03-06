// IMP Project - Robert Lehmann 2020-2021


#include "IMPInventoryComponent.h"
#include "IMPBase/Utility/IMPInventoryItemBase.h"


UIMPInventoryComponent::UIMPInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UIMPInventoryComponent::AddItem(UIMPInventoryItemBase* Item)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - InventoryComponent: Tried to add invalid item"), *GetOwner()->GetName());
		return false;
	}

	if (!Item->IsPendingKill())
	{
		// add to the stack if possible
		int32 ItemIndex = GetValidStackIndex(Item);
		if (Items.IsValidIndex(ItemIndex))
		{
			int32 Stack, StackSize, StackDelta;

			Stack = Items[ItemIndex]->ItemStack + Item->ItemStack;
			StackSize = Items[ItemIndex]->ItemStackSize;
			StackDelta = Stack - StackSize;

			if(StackDelta > 0)
			{
				Items[ItemIndex]->ItemStack = StackSize;
				Item->ItemStack = StackDelta;
			}
			else
			{
				Items[ItemIndex]->ItemStack += Item->ItemStack;
				
				OnInventoryUpdated.Broadcast();
				return true;
			}
		}

		//else add the item to the inventory as a new stack
		Item->SetOwner(this);
		Item->SetWorld(GetWorld());

		Items.Add(Item);

		OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}

bool UIMPInventoryComponent::AddItemByClass(TSubclassOf<class UIMPInventoryItemBase> ItemClass)
{
	UIMPInventoryItemBase* Item = Cast<UIMPInventoryItemBase>(ItemClass->GetDefaultObject(false));

	if (Item)
	{
		if (!Item->IsPendingKill())
		{
			// add to the stack if possible
			int32 ItemIndex = GetValidStackIndex(Item);
			if (Items.IsValidIndex(ItemIndex))
			{
				Items[ItemIndex]->ItemStack++;
				
				OnInventoryUpdated.Broadcast();
				return true;
			}

			// else create a new object and add it to the inventory as a new stack
			Item = Cast<UIMPInventoryItemBase>(StaticConstructObject_Internal(ItemClass));

			Item->SetOwner(this);
			Item->SetWorld(GetWorld());

			Items.Add(Item);

			Item = nullptr;

			OnInventoryUpdated.Broadcast();
			return true;
		}
	}

	return false;
}

bool UIMPInventoryComponent::RemoveItem(UIMPInventoryItemBase* Item, const bool bDestroyItem)
{
	if (Item)
	{
		if (!Item->IsPendingKill())
		{
			if (Item->ItemStack > 1)
			{
				Item->ItemStack--;

				OnInventoryUpdated.Broadcast();
				return true;
			}
			else
			{
				Items.RemoveSingle(Item);
				
				if (bDestroyItem)
				{
					Item->MarkForDestruction();
					Item = nullptr;
				}

				OnInventoryUpdated.Broadcast();
				return true;
			}
		}
	}

	return false;
}

bool UIMPInventoryComponent::TransferItem(class UIMPInventoryItemBase* Item, UIMPInventoryComponent* TargetInventory, bool bTakeWholeStack)
{
	if (Item)
	{
		if (bTakeWholeStack || Item->ItemStack == 1)
		{
			Items.RemoveSingle(Item);
			TargetInventory->AddItem(Item);
		}
		else
		{
			if (Item->ItemStack > 1)
			{
				Item->ItemStack--;
				TargetInventory->AddItemByClass(Item->GetClass());
			}
			else
			{
				// just in case we encounter an item with stack < 1
				return false;
			}
		}

		OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}

bool UIMPInventoryComponent::TransferAll(UIMPInventoryComponent* TargetInventory)
{
	if (TargetInventory)
	{
		for (UIMPInventoryItemBase* Item : Items)
		{
			TransferItem(Item, TargetInventory, true);
		}

		return true;
	}

	return false;
}

void UIMPInventoryComponent::Sort()
{
	// TODO: Unifiy stacks of identical items

	Items.StableSort();
}

UIMPInventoryItemBase* UIMPInventoryComponent::FindItem(TSubclassOf<UIMPInventoryItemBase> ItemClass) const
{
	const UIMPInventoryItemBase* Item = Cast<UIMPInventoryItemBase>(ItemClass->GetDefaultObject(false));

	if (Item)
	{
		for (int32 i = Items.Num() - 1; i >= 0; i--)
		{
			if (*Items[i] == *Item)
			{
				return Items[i];
			}
		}
	}

	return nullptr;
}

void UIMPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (UIMPInventoryItemBase* Item : StartupItems)
	{
		AddItem(Item);
	}

	Sort();
}

int32 UIMPInventoryComponent::GetValidStackIndex(const UIMPInventoryItemBase* Item) const
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (*Items[i] == *Item && Items[i]->ItemStack < Items[i]->ItemStackSize)
		{
			return i;
		}
	}

	return -1;
}


