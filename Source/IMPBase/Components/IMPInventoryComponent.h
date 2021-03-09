// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IMPInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

/* A component that adds an inventory able to hold UIMPInventoryItemBase objects for any actor it is attached to. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPBASE_API UIMPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced, Category = "IMP Base|Inventory", meta = (AllowPrivateAccess = "true"))
	/* Use this to define items that will get added to this component when initially spawned */
	TArray<class UIMPInventoryItemBase*> StartupItems;

public:	

	UIMPInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	/* Delegate that is called everytime an Item is either added or removed */
	FOnInventoryUpdated OnInventoryUpdated;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	/* Holds all items currently stored in this component. Read-Only.*/
	TArray<class UIMPInventoryItemBase*> Items;
	
	UFUNCTION(BlueprintCallable)
	/** Adds an already existing item to this inventory component. 
	* Provided the item is stackable, the item will be added to the next valid stack by incrementing it. 
	* Otherwise it will be added to the inventory as a new stack. If the item is not stackable it will be added as a new entry. 
	* This function will not create any new object instances.
	* @param Item - The item that will be added to this component
	* @return True if the Item was successfully added, otherwise false.
	*/
	bool AddItem(class UIMPInventoryItemBase* Item);
	
	UFUNCTION(BlueprintCallable)
	/** Potentially spawns a new instance of the item and adds it to this inventory component. 
	* Provided the item is stackable, the item will be added to the next valid stack by incrementing it. 
	* Otherwise it will CREATE a new instance of the item object and add it to the inventory as a new stack. 
	* If the item is not stackable it will be created and added as a new entry.
	* @param ItemClass - The item type by class that will be created and added to this component
	* @return True if the Item was successfully added, otherwise false.
	*/
	bool AddItemByClass(TSubclassOf<class UIMPInventoryItemBase> ItemClass);

	UFUNCTION(BlueprintCallable)
	/** Removes an item from the inventory component and potentially the game world.  
	* Provided the item is stackable, the item will be removed from the next valid stack by decrementing it. 
	* Otherwise it will just remove the item from the inventory. By default bDestroyItem marks it also for destruction so it can be picked up by the garbage collector. 
	* It is unsafe to reference the item afterwards!
	* @param Item - The item that will be removed
	* @param bDestroyItem - If true the item will be marked for destruction, removing it from the world.
	* @return True if the Item was successfully removed, otherwise false.
	*/
	bool RemoveItem(class UIMPInventoryItemBase* Item, const bool bDestroyItem = true);

	UFUNCTION(BlueprintCallable)
	/** Moves an exisiting item from this inventory to another inventory component. Provided the item is stackable,
	* the item will be added to the next valid stack by incrementing it. Otherwise it will CREATE a new instance of the item object
	* and add it to the inventory as a new stack.
	* @param Item - The item to be moved
	* @param TargetInventory - The inventory that will receive the moved item
	* @param bTakeWholeStack - True will move the complete stack. False will move items in stacks individually. Defaults to false
	* @return True if the Item was successfully transfered, otherwise false.
	* 
	* NOTE: Update the function to return a reference to the item being transfered rather than a bool. Useful for the UI if we happen to create a new item by splitting a stack.
	*/
	bool TransferItem(class UIMPInventoryItemBase* Item, UIMPInventoryComponent* TargetInventory, bool bTakeWholeStack = false);

	UFUNCTION(BlueprintCallable)
	/** Moves all items from this inventory to another inventory component.
	* @param TargetInventory - The inventory that will receive the moved items
	* @return True if the Items were successfully transfered, otherwise false.
	*/
	bool TransferAll(UIMPInventoryComponent* TargetInventory);

	UFUNCTION(BlueprintCallable)
	/* Sorts the inventory. Uses a stable sorting algorythm. */
	void Sort();

	UFUNCTION(BlueprintCallable)
	/** Tries to find an item inside the inventory. The search is backwards.
	* @param ItemClass - The item type to look for.
	* @return A pointer to the item if successful, otherwise nullptr.
	*/
	class UIMPInventoryItemBase* FindItem(TSubclassOf<class UIMPInventoryItemBase> ItemClass) const;

protected:

	virtual void BeginPlay() override;
	
private:

	int32 GetValidStackIndex(const class UIMPInventoryItemBase* Item) const;
};
