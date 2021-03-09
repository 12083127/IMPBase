// IMP Project - Robert Lehmann 2020-2021


#include "IMPPreviewPlayerWidget.h"
#include "IMPBase/IMPBaseGameMode.h"
#include "IMPBase/Actor/IMPPreviewCaptureBase.h"

void UIMPPreviewPlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UWorld* const World = GetWorld();
	AIMPBaseGameMode* const GM = Cast<AIMPBaseGameMode>(World->GetAuthGameMode());

	if (GM)
	{
		AIMPPreviewCaptureBase* const CaptureActor = Cast<AIMPPreviewCaptureBase>(GM->GetPlayerPreviewActor());
		if (CaptureActor)
		{
			PreviewActor = CaptureActor;
		}
		else
		{
			if (PreviewActorClass)
			{
				const FVector Loc(0.f, 0.f, 6000000.f);

				PreviewActor = World->SpawnActor<AIMPPreviewCaptureBase>(PreviewActorClass, Loc, FRotator());
				GM->SetPlayerPreviewActor(PreviewActor);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s: Please add a valid Preview Actor Class inside the Preview Widget!"), *this->GetName());
			}
		}
	}
}

void UIMPPreviewPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetCapturePreview(true);
}

void UIMPPreviewPlayerWidget::NativeDestruct()
{
	Super::NativeDestruct();

	SetCapturePreview(false);
}

FReply UIMPPreviewPlayerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return OnMouseButton(true);
}

FReply UIMPPreviewPlayerWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return OnMouseButton(false);
}

void UIMPPreviewPlayerWidget::SetCapturePreview(const bool bEnabled)
{
	if (PreviewActor)
	{
		PreviewActor->SetCapturePreview(bEnabled);
	}
}

void UIMPPreviewPlayerWidget::UpdatePreview(UIMPInventoryItemBase* const Item)
{
	if (PreviewActor)
	{
		PreviewActor->UpdatePreviewMesh(nullptr);
	}
}

void UIMPPreviewPlayerWidget::RotateMeshPreview(FVector2D InMouseLocation)
{
	if (PreviewActor)
	{
		FVector2D MouseLoc = InMouseLocation;
		MouseLoc.Y *= 0.f;
		PreviewActor->RotateMeshPreview(MouseLoc);
	}
}

void UIMPPreviewPlayerWidget::SetUserRotation(const bool bEnabled, const FVector2D MouseLocationStart)
{
	if (PreviewActor)
	{
		FVector2D MouseLoc = MouseLocationStart;
		MouseLoc.Y *= 0.f;
		PreviewActor->SetUserRotation(bEnabled, MouseLoc);
	}
}

FReply UIMPPreviewPlayerWidget::OnMouseButton(const bool bClicked)
{
	APlayerController* PC = GetOwningPlayer();

	if (PreviewActor && PC)
	{
		FVector2D MouseLoc;
		PC->GetMousePosition(MouseLoc.X, MouseLoc.Y);
		MouseLoc.Y *= 0.f;

		PreviewActor->SetUserRotation(bClicked, MouseLoc);

		return FReply::Handled();
	}

	return FReply::Unhandled();
}
