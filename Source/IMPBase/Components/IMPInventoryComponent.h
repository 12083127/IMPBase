// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IMPInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPBASE_API UIMPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "IMP Base|Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<class UIMPInventoryItemBase*> StartupItems;

public:	

	UIMPInventoryComponent();

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UIMPInventoryItemBase*> Items;
	
	UFUNCTION(BlueprintCallable)
	bool AddItem(class UIMPInventoryItemBase* Item);
	
	UFUNCTION(BlueprintCallable)
	bool AddItemByClass(TSubclassOf<class UIMPInventoryItemBase> ItemClass);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(class UIMPInventoryItemBase* Item);

	UFUNCTION(BlueprintCallable)
	void Sort();

	UFUNCTION(BlueprintCallable)
	class UIMPInventoryItemBase* FindItem(TSubclassOf<class UIMPInventoryItemBase> ItemClass);

protected:

	virtual void BeginPlay() override;
	
private:

	int32 GetValidStackIndex(class UIMPInventoryItemBase* Item);
};
