// IMP Project - Robert Lehmann 2020-2021


#include "IMPPreviewMeshWidget.h"
#include "IMPBase/IMPBaseGameMode.h"
#include "IMPBase/Actor/IMPPreviewCaptureBase.h"
#include "Input/Reply.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UIMPPreviewMeshWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UWorld* const World = GetWorld();
	AIMPBaseGameMode* const GM = Cast<AIMPBaseGameMode>(World->GetAuthGameMode());

	if (GM)
	{
		AIMPPreviewCaptureBase* const CaptureActor = Cast<AIMPPreviewCaptureBase>(GM->GetItemPreviewActor());
		if (CaptureActor)
		{
			PreviewActor = CaptureActor;
		}
		else
		{
			if (PreviewActorClass)
			{
				const FVector Loc(0.f, 0.f, 5000000.f);

				PreviewActor = World->SpawnActor<AIMPPreviewCaptureBase>(PreviewActorClass, Loc, FRotator());
				GM->SetItemPreviewActor(PreviewActor);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: Please add a valid Preview Actor Class inside the Preview Widget!"), *this->GetName());
			}
		}
	}
}

void UIMPPreviewMeshWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PreviewActor)
	{
		PreviewActor->SetCapturePreview(true);
		PreviewActor->SetIdleRotationActive(true);
	}
}

void UIMPPreviewMeshWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (PreviewActor)
	{
		PreviewActor->SetCapturePreview(false);
	}
}

FReply UIMPPreviewMeshWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return OnMouseButton(true);
}

FReply UIMPPreviewMeshWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return OnMouseButton(false);
}

void UIMPPreviewMeshWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (PreviewActor)
	{
		PreviewActor->SetIdleRotationActive(false);
	}
}

void UIMPPreviewMeshWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (PreviewActor)
	{
		PreviewActor->SetIdleRotationActive(true);
	}
}

void UIMPPreviewMeshWidget::SetCapturePreview(const bool bEnabled)
{
	if (PreviewActor)
	{
		PreviewActor->SetCapturePreview(bEnabled);
	}
}

void UIMPPreviewMeshWidget::UpdatePreview(UIMPInventoryItemBase* const Item)
{
	if (PreviewActor)
	{
		PreviewActor->UpdatePreviewMesh(Item);
	}
}

void UIMPPreviewMeshWidget::RotateMeshPreview(FVector2D InMouseLocation)
{
	if (PreviewActor)
	{
		PreviewActor->RotateMeshPreview(InMouseLocation);
	}
}

void UIMPPreviewMeshWidget::SetUserRotation(const bool bEnabled, const FVector2D MouseLocationStart)
{
	if (PreviewActor)
	{
		PreviewActor->SetUserRotation(bEnabled, MouseLocationStart);
	}
}

FReply UIMPPreviewMeshWidget::OnMouseButton(const bool bClicked)
{
	APlayerController* PC = GetOwningPlayer();

	if (PreviewActor && PC)
	{
		FVector2D MouseLoc;
		PC->GetMousePosition(MouseLoc.X, MouseLoc.Y);

		const float DPIScale = 1/UWidgetLayoutLibrary::GetViewportScale(GetWorld());

		PreviewActor->SetUserRotation(bClicked, MouseLoc * DPIScale);

		return FReply::Handled();
	}

	return FReply::Unhandled();
}