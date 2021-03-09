// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "IMPListEntryBase.generated.h"

/* Base UI Widget List Entry class that handles some basic input and visual logic like changing colors based on different states. */
UCLASS()
class IMPBASE_API UIMPListEntryBase : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	/* Mark this List Entry as selected or deselected. Usually used in conjunction with the OnItemSelectionChanged Interface call provided by IUserObjectListEntry.*/
	void MarkSelected(const bool bSelected);

	UFUNCTION(BlueprintCallable)
	/*Resets the List Entry to its default state.*/
	void InitializeListEntry();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Normal", meta = (DisplayName = "Background"))
	FLinearColor BackgroundColorDefault;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Hovered", meta = (DisplayName = "Background"))
	FLinearColor BackgroundColorHovered;
	
	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Selected", meta = (DisplayName = "Background"))
	FLinearColor BackgroundColorSelected;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Normal", meta = (DisplayName = "Border"))
	FLinearColor BorderColorDefault;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Hovered", meta = (DisplayName = "Border"))
	FLinearColor BorderColorHovered;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Selected", meta = (DisplayName = "Border"))
	FLinearColor BorderColorSelected;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Normal", meta = (DisplayName = "Content"))
	FLinearColor ForegroundColorDefault;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Hovered", meta = (DisplayName = "Content"))
	FLinearColor ForegroundColorHovered;

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|Selected", meta = (DisplayName = "Content"))
	FLinearColor ForegroundColorSelected;

	UPROPERTY(meta = (BindWidget))
	class UBorder* EntryBackground;

	UPROPERTY(meta = (BindWidget))
	class UBorder* EntryBorder;

	virtual void NativeConstruct() override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:

	bool bSelected;

	void SetListEntryColors(FLinearColor InBackgroundColor, FLinearColor InBorderColor, FLinearColor InForegroundColor);
};
