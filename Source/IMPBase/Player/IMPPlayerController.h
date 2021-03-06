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

	UFUNCTION(BlueprintCallable)
	/*Checks if the Note you want to add is valid and adds it to the players journal as an IMPJournalEntryObject.
	* @param Note - The note to be added.
	* @return True if successful, otherwise false
	*/
	bool AddNewJournalEntry(const FIMPNoteEntry Note);

	UFUNCTION(BlueprintCallable)
	/*@return Gets all entries inside the players journal. */
	FORCEINLINE TArray<class UIMPJournalEntryObject*> GetPlayerNoteJournal() const { return PlayerNoteJournal; }

private:
	TArray<class UIMPJournalEntryObject*> PlayerNoteJournal;
};
