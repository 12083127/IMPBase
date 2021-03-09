// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/StaticArray.h"
#include "IMPBase/Utility/IMPEquipmentItemBase.h"
#include "IMPEquipmentComponent.generated.h"

#define MAXEquipmentSlots		StaticCast<int32>(EEquipmentSlot::LENGTH)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPBASE_API UIMPEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "IMP Base|Equipment", meta = (AllowPrivateAccess = "true"))
	// NOTE: Designers should not be able to add further entries inside editor. Further research needed
	TArray<UIMPEquipmentItemBase*> StartupEquipment;

public:	
	// Sets default values for this component's properties
	UIMPEquipmentComponent();

	UPROPERTY(BlueprintAssignable)
	FOnEquipmentUpdated OnEquipmentUpdated;

	UFUNCTION(BlueprintCallable)
	UIMPEquipmentItemBase* EquipItem(UIMPEquipmentItemBase* const Item);

	UFUNCTION(BlueprintCallable)
	UIMPEquipmentItemBase* UnequipItem(const EEquipmentSlot InSlot);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UIMPEquipmentItemBase*> GetEquippedItems() const { return Equipment; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TArray<UIMPEquipmentItemBase*> Equipment;

	int32 GetSlotIndex(const EEquipmentSlot Slot) const;
};
