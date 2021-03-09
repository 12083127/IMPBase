// IMP Project - Robert Lehmann 2020-2021


#include "IMPHUD.h"
#include "Blueprint/UserWidget.h"
#include "IMPBase/Player/IMPPlayerController.h"

AIMPHUD::AIMPHUD()
{

}

bool AIMPHUD::IsMenuScreenActive(UUserWidget* InWidget) const
{
	if (InWidget)
	{
		return InWidget->IsVisible();
	}

	return false;
}

void AIMPHUD::ShowPlayerHUD()
{
	ShowWidget(DefaultPlayerHUDClass, DefaultPlayerHUD);
}

void AIMPHUD::HidePlayerHUD()
{
	HideWidget(DefaultPlayerHUD);
}

void AIMPHUD::ShowPlayerMenu()
{
	//ShowWidget(PlayerMenuClass, PlayerMenu);

	if (ShowWidget(PlayerMenuClass, PlayerMenu))
	{
		HidePlayerHUD();

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PlayerMenu->GetCachedWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);

		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(InputMode);
		PlayerOwner->SetPause(true);
	}
}

void AIMPHUD::HidePlayerMenu()
{
	HideWidget(PlayerMenu);
	ShowPlayerHUD();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
	PlayerOwner->SetPause(false);
}

void AIMPHUD::ShowGameMenu()
{
	ShowWidget(GameMenuClass, GameMenu);
}

void AIMPHUD::HideGameMenu()
{
	HideWidget(GameMenu);
}

void AIMPHUD::ShowContainerScreen(AIMPContainerBase* const Container)
{
	//ShowWidget(ContainerScreenClass, ContainerScreen);

	if (ShowWidget(ContainerScreenClass, ContainerScreen))
	{
		HidePlayerHUD();

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(ContainerScreen->GetCachedWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);

		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(InputMode);
		PlayerOwner->SetPause(true);
	}
}

void AIMPHUD::HideContainerScreen()
{
	HideWidget(ContainerScreen);
	ShowPlayerHUD();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
	PlayerOwner->SetPause(false);
}

void AIMPHUD::TogglePlayerMenu()
{
	const bool bGameMenuInactive = !IsMenuScreenActive(GameMenu);
	const bool bContainerScreenInactive = !IsMenuScreenActive(ContainerScreen);

	if (bGameMenuInactive && bContainerScreenInactive)
	{
		if (IsMenuScreenActive(PlayerMenu))
		{
			HidePlayerMenu();
		}
		else
		{
			ShowPlayerMenu();
		}
	}
}

void AIMPHUD::HideWidget(UUserWidget* InWidget)
{
	if (InWidget)
	{
		InWidget->RemoveFromViewport();
	}
}

UUserWidget* AIMPHUD::ShowWidget(TSubclassOf<class UUserWidget> WidgetClass, UUserWidget*& OutWidget)
{
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Widget Class. Please assign a valid Widget Class in HUD Class."));
		return nullptr;
	}

	if (!OutWidget)
	{
		OutWidget = CreateWidget<UUserWidget>(PlayerOwner, WidgetClass);
	}

	OutWidget->AddToViewport();
	return OutWidget;
}
