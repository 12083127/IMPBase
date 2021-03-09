// IMP Project - Robert Lehmann 2020-2021


#include "IMPListEntryBase.h"
#include "Components/Border.h"

void UIMPListEntryBase::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeListEntry();
}

void UIMPListEntryBase::NativeOnItemSelectionChanged(bool bIsSelected)
{
	MarkSelected(bIsSelected);
}

void UIMPListEntryBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	SetListEntryColors(BackgroundColorHovered, BorderColorHovered, ForegroundColorHovered);
}

void UIMPListEntryBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (!bSelected)
	{
		SetListEntryColors(BackgroundColorDefault, BorderColorDefault, ForegroundColorDefault);
	}
	else
	{
		SetListEntryColors(BackgroundColorSelected, BorderColorSelected, ForegroundColorSelected);
	}
}

void UIMPListEntryBase::MarkSelected(const bool bIsSelected)
{
	bSelected = bIsSelected;

	if (bSelected)
	{
		SetListEntryColors(BackgroundColorSelected, BorderColorSelected, ForegroundColorSelected);
	}
	else
	{
		SetListEntryColors(BackgroundColorDefault, BorderColorDefault, ForegroundColorDefault);
	}
}

void UIMPListEntryBase::InitializeListEntry()
{
	MarkSelected(false);
}

void UIMPListEntryBase::SetListEntryColors(FLinearColor InBackgroundColor, FLinearColor InBorderColor, FLinearColor InForegroundColor)
{
	FSlateBrush Brush;

	Brush.TintColor = FSlateColor(InBackgroundColor);

	EntryBackground->SetBrush(Brush);
	EntryBorder->SetBrushColor(InBorderColor);
	EntryBorder->SetContentColorAndOpacity(InForegroundColor);
}
