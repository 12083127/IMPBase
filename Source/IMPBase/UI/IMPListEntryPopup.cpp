// IMP Project - Robert Lehmann 2020-2021


#include "IMPListEntryPopup.h"


void UIMPListEntryPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PopupClass)
	{
		if (!PopupReference)
		{
			PopupReference = CreateWidget<UUserWidget>(GetOwningPlayer(), PopupClass);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign a valid Popup Class inside to spawn a popup."));
	}
}

void UIMPListEntryPopup::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (PopupReference)
	{
		PopupReference->AddToViewport();
		PopupReference->SetPositionInViewport(PopupPosition);
	}
}

void UIMPListEntryPopup::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (PopupReference)
	{
		PopupReference->RemoveFromParent();
	}
}

void UIMPListEntryPopup::SetPopupPosition(const FVector2D InPosition)
{
	PopupPosition = InPosition;
}