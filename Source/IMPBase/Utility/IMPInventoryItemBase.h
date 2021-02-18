// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IMPBase/Utility/IMPInventoryItemInterface.h"
#include "IMPInventoryItemBase.generated.h"

UENUM(BlueprintType)
enum class EInventoryItemCategory : uint8
{
	IC_None UMETA(DisplayName = "None"),
	IC_Armor UMETA(DisplayName = "Armor"),
	IC_Consumeable UMETA(DisplayName = "Consumeable")
};
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class IMPBASE_API UIMPInventoryItemBase : public UObject, public IIMPInventoryItemInterface
{
	GENERATED_BODY()
	
public:

	UIMPInventoryItemBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EInventoryItemCategory ItemCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	int32 ItemValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1))
	int32 ItemStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1))
	int32 ItemStackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.f))
	float ItemWeight;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UIMPInventoryComponent* GetOwner() const { return Owner; }

	UFUNCTION(BlueprintCallable)
	virtual class UWorld* GetWorld() const { return World; }

	void SetOwner(class UIMPInventoryComponent* NewOwner);
	void SetWorld(class UWorld* NewWorld);
	void MarkForDestruction();
	
	// operator overloading to check for duplicates and sorting algorithms
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

private:

	UPROPERTY(Transient)
	class UWorld* World;

	class UIMPInventoryComponent* Owner;
};
