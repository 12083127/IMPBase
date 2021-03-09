// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IMPBase/IMPBase.h"
#include "IMPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class IMPBASE_API AIMPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AIMPPlayerController();

	static const FName CharMenuBinding;

	UFUNCTION(BlueprintCallable)
	/*Checks if the Note you want to add is valid and adds it to the players journal as an IMPJournalEntryObject.
	* @param Note - The note to be added.
	* @return True if successful, otherwise false
	*/
	bool AddNewJournalEntry(const FIMPNoteEntry Note);

	UFUNCTION(BlueprintCallable)
	/*@return Pointer to the currently active container that is being looted. */
	FORCEINLINE class AIMPContainerBase* GetActiveContainer() const { return ActiveContainerRef; }
	
	UFUNCTION(BlueprintCallable)
	/*@return Gets all entries inside the players journal. */
	FORCEINLINE TArray<class UIMPJournalEntryObject*> GetPlayerNoteJournal() const { return PlayerNoteJournal; }

	void ShowContainerScreen(class AIMPContainerBase* const Container);
	void HideContainerScreen();
	class UUserWidget* GetContainerScreen() const;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY()
	class AIMPContainerBase* ActiveContainerRef;

	UPROPERTY()
	class AIMPHUD* PlayerHUD;

	UPROPERTY()
	/* Holds all the notes that the player has found */
	TArray<class UIMPJournalEntryObject*> PlayerNoteJournal;

	void TogglePlayerMenu();
};
