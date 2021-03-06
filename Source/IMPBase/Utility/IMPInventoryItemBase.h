// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IMPBase/Utility/IMPInventoryItemInterface.h"
#include "IMPInventoryItemBase.generated.h"

UENUM(BlueprintType)
/* All item categories available for inventory items to filter items by type*/
enum class EInventoryItemCategory : uint8
{
	IC_None UMETA(DisplayName = "None"),
	IC_Armor UMETA(DisplayName = "Armor"),
	IC_Consumeable UMETA(DisplayName = "Consumeable")
};

/** Base class that holds all necessary properties and function calls every inventory item needs.
* This class is also necessary to create list entries for the GUI representation of the inventory.
*/
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class IMPBASE_API UIMPInventoryItemBase : public UObject, public IIMPInventoryItemInterface
{
	GENERATED_BODY()
	
public:

	UIMPInventoryItemBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* Unqiue ID for every item. NOTE: This is used to compare and InventoryItem objects. Usually not exposed to the player. */
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* Item category the object belongs to. */
	EInventoryItemCategory ItemCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* A 3D Mesh representing the item in a preview. */
	class UStaticMesh* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* The actual name of the item. This will be exposed to the player. */
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* A short item description of the item. */
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	/* How much this item is worth in the given currency. Default: 0 */
	int32 ItemValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1))
	/* The current amount of items in the stack. Min: 1*/
	int32 ItemStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1))
	/* How high you can stack the item until a new stack is created. Leave at 1 to not use stacking. Min: 1*/
	int32 ItemStackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.f))
	/* How much this item weighs. */
	float ItemWeight;

	UFUNCTION(BlueprintCallable)
	/*@return Reference to the inventory component this item is currently part of. */
	FORCEINLINE class UIMPInventoryComponent* GetOwner() const { return Owner; }

	UFUNCTION(BlueprintCallable)
	/*@return Reference to the game world the item resides */
	virtual class UWorld* GetWorld() const { return World; }

	UFUNCTION(BlueprintCallable)
	/*@return Reference to the List Entry Widget this item currently represents in the GUI */
	FORCEINLINE class UWidget* GetEntryWidget() const { return CurrentEntryWidget; }

	UFUNCTION(BlueprintCallable)
	/** Used to set the current List Entry Widget this item represents in the GUI
	* @param InWidget - Reference to the widget that is set to be the current widget
	*/
	void SetEntryWidget(class UWidget* InWidget);

	UFUNCTION(BlueprintCallable)
	/* Clears the current widget reference, setting it to nullptr. */
	void ClearEntryWidget();

	void SetOwner(class UIMPInventoryComponent* NewOwner);
	void SetWorld(class UWorld* NewWorld);
	void MarkForDestruction();

	virtual void OnUse();

	// operator overloading to check for duplicates and to enable sorting algorithms
	bool operator==(const UIMPInventoryItemBase& Item) const
	{
		if (ItemID == Item.ItemID)
			return true;
		else
			return false;
	}

	friend bool operator<(const UIMPInventoryItemBase& a, const UIMPInventoryItemBase& b)
	{
		return (uint8)a.ItemCategory < (uint8)b.ItemCategory && a.ItemStack < b.ItemStack;
	}

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginDestroy();

private:

	UPROPERTY(Transient)
	class UWorld* World;

	class UIMPInventoryComponent* Owner;
	class UWidget* CurrentEntryWidget;

};
