// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/UI/IMPListEntryBase.h"
#include "IMPListEntryPopup.generated.h"

/* A basic UI List Entry Widget that can spawn a Popup when hovering over the List Entry itself.*/
UCLASS()
class IMPBASE_API UIMPListEntryPopup : public UIMPListEntryBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	/* The widget that will be spawned upon hovering over this widget*/
	TSubclassOf<class UUserWidget> PopupClass;

	UFUNCTION(BlueprintCallable)
	/* Sets the position of the popup widget to value passed in InPosition */
	void SetPopupPosition(const FVector2D InPosition);

	UFUNCTION(BlueprintCallable)
	/*@return Pointer to the spawned Popup for later reference.*/
	FORCEINLINE class UUserWidget* GetPopup() const { return PopupReference; }

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:

	FVector2D PopupPosition;

	UPROPERTY()
	class UUserWidget* PopupReference;
};
