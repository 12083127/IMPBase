// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "IMPBase/IMPBase.h"
#include "IMPBaseGameMode.generated.h"

UCLASS(minimalapi)
class AIMPBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AIMPBaseGameMode();

	UFUNCTION(BlueprintCallable)
	/*Looks for a Note Entry by ID inside the note data table and passes it into OutEntry.
	* @param NoteID - NoteID of the note you are looking for
	* @param OutEntry - Note Entry output if found one
	* @return True and the NoteEntry if successful, otherwise false
	*/
	bool GetNoteEntryFromDB(const FName NoteID, FIMPNoteEntry& OutEntry);

	//UFUNCTION(BlueprintCallable)
	// remove blueprint callable when finished prototyping!
	void SetItemPreviewActor(class AIMPPreviewCaptureBase* const PreviewActor);

	//UFUNCTION(BlueprintCallable)
	// remove blueprint callable when finished prototyping!
	void SetPlayerPreviewActor(class AIMPPreviewCaptureBase* const PreviewActor);

	UFUNCTION(BlueprintCallable)
	bool SetGamePaused(const bool bPaused);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AIMPPreviewCaptureBase* GetItemPreviewActor() const { return ItemPreviewActor; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AIMPPreviewCaptureBase* GetPlayerPreviewActor() const { return PlayerPreviewActor; }

protected:

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base")
	/* Reference to the data table that holds all note entries. NoteID and RowName in the data table need to be identical! */
	const UDataTable* NoteDataTable;

private:

	UPROPERTY()
	class AIMPPreviewCaptureBase* ItemPreviewActor;

	UPROPERTY()
	class AIMPPreviewCaptureBase* PlayerPreviewActor;
};



