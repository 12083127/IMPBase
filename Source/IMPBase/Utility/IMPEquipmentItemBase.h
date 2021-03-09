// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Utility/IMPInventoryItemBase.h"
#include "IMPEquipmentItemBase.generated.h"

UENUM(BlueprintType)
/* All available Equipment slots available to the game. */
enum class EEquipmentSlot : uint8
{
	ES_Head UMETA(Displayname = "Head"),
	ES_Body UMETA(Displayname = "Body"),
	ES_Boots UMETA(Displayname = "Boots"),
	ES_MainWeapon UMETA(Displayname = "Main Weapon"),
	LENGTH UMETA(Hidden)
};
/* Basic class for all inventory items that are equippable. */
UCLASS()
class IMPBASE_API UIMPEquipmentItemBase : public UIMPInventoryItemBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* Defines which equipment slot this item will occupy.*/
	EEquipmentSlot ItemSlotType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	/* Protective value this armor piece provides */
	int32 ArmorRating;

	virtual void OnUse() override;

	//UFUNCTION(BlueprintCallable)
	///*@return Reference to the Equipment component this item is currently part of. */
	//FORCEINLINE class UIMPEquipmentComponent* GetOwner() const { return Owner; }

	//void SetOwner(class UIMPEquipmentComponent* const NewOwner);

private:

	//class UIMPEquipmentComponent* Owner;
};
