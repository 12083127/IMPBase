// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IMPHUD.generated.h"

/* This class handles most of the UI logic, spawning and despawning widgets. User created Widget classes can be set here to spawn automatically.*/
UCLASS(Abstract)
class IMPBASE_API AIMPHUD : public AHUD
{
	GENERATED_BODY()

public:
	AIMPHUD();

	UFUNCTION(BlueprintCallable)
	/*@return True if InWidget is visible otherwise false. */
	bool IsMenuScreenActive(UUserWidget* InWidget) const;

	UFUNCTION(Blueprintcallable)
	/*@return Pointer to the default Player HUD. */
	FORCEINLINE class UUserWidget* GetDefaultPlayerHUD() const { return DefaultPlayerHUD; }

	UFUNCTION(Blueprintcallable)
	/*@return Pointer to the Player Menu. */
	FORCEINLINE	class UUserWidget* GetPlayerMenu() const { return PlayerMenu; }

	UFUNCTION(Blueprintcallable)
	/*@return Pointer to the Game Menu. */
	FORCEINLINE class UUserWidget* GetGameMenu() const { return GameMenu; }

	UFUNCTION(Blueprintcallable)
	/*@return Pointer to the Container Screen. */
	FORCEINLINE class UUserWidget* GetContainerScreen() const { return ContainerScreen; }

	UFUNCTION(BlueprintCallable)
	/* Shows HUD by adding it to the viewport. */
	void ShowPlayerHUD();

	UFUNCTION(BlueprintCallable)
	/* Hides HUD by removing it from the viewport. */
	void HidePlayerHUD();

	UFUNCTION(BlueprintCallable)
	/* Shows Player Menu by adding it to the viewport. */
	void ShowPlayerMenu();

	UFUNCTION(BlueprintCallable)
	/* Hides Player Menu by removing it from the viewport. */
	void HidePlayerMenu();

	UFUNCTION(BlueprintCallable)
	/* Shows Game Menu by adding it to the viewport. */
	void ShowGameMenu();

	UFUNCTION(BlueprintCallable)
	/* Hides Game Menu by removing it from the viewport. */
	void HideGameMenu();

	UFUNCTION(BlueprintCallable)
	/* Shows Container Screen by adding it to the viewport. */
	void ShowContainerScreen(class AIMPContainerBase* const Container);

	UFUNCTION(BlueprintCallable)
	/* Hides Container Screen by removing it from the viewport. */
	void HideContainerScreen();

	void TogglePlayerMenu();

protected:

	UPROPERTY(EditDefaultsOnly)
	/* Widget Class for the default player HUD. */
	TSubclassOf<class UUserWidget> DefaultPlayerHUDClass;

	UPROPERTY(EditDefaultsOnly)
	/* Widget Class that gets spawned when opening the Player Menu. */
	TSubclassOf<class UUserWidget> PlayerMenuClass;

	UPROPERTY(EditDefaultsOnly)
	/* Widget Class that gets spawned when opening the Game Menu. */
	TSubclassOf<class UUserWidget> GameMenuClass;

	UPROPERTY(EditDefaultsOnly)
	/* Widget Class that gets spawned when opening a container ingame. */
	TSubclassOf<class UUserWidget> ContainerScreenClass;

private:

	UPROPERTY()
	class UUserWidget* DefaultPlayerHUD;

	UPROPERTY()
	class UUserWidget* PlayerMenu;
	
	UPROPERTY()
	class UUserWidget* GameMenu;
	
	UPROPERTY()
	class UUserWidget* ContainerScreen;

	class UUserWidget* ShowWidget(TSubclassOf<class UUserWidget> WidgetClass, class UUserWidget*& OutWidget);
	void HideWidget(class UUserWidget* Widget);


};
