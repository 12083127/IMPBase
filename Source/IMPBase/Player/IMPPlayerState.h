// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerState.h"
#include "IMPBase/IMPBase.h"
#include "IMPPlayerState.generated.h"

USTRUCT(BlueprintType)
struct FIMPNoteEntry : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NoteID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NoteHeading;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NoteBody;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENoteCategory NoteCategory;

	// operator overloading to check for duplicates
	bool operator==(const FIMPNoteEntry& Note) const
	{
		if (NoteID == Note.NoteID)
			return true;
		else
			return false;
	}
};

/**
 * 
 */
UCLASS()
class IMPBASE_API AIMPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AIMPPlayerState();
	
	UPROPERTY(VisibleAnywhere, Category = "IMP Base")
	/** Holds all the notes the player has found */
	TArray<FIMPNoteEntry> PlayerNoteJournal;

	UFUNCTION(BlueprintCallable)
	/** Checks if the Note you want to add is valid and adds it to the players journal.
	 *  @param Note - The note to be added.
	 */
	void AddNoteToPlayerJournal(const FIMPNoteEntry Note);

	UFUNCTION(BlueprintCallable)
	/** Looks for a Note Entry and returns it as a struct for later use 
	 *  @param NoteID - NoteID of the note you are looking for.
	 */
	FIMPNoteEntry FindNoteEntry(const FName NoteID) const;

	//FORCEINLINE class UDataTable* GetNoteJournalDB() const { return NoteDataTable; }

protected:

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base")
	/** Reference to the data table that holds all note entries. NoteID and RowName in the data table need to be identical! */
	const UDataTable* NoteDataTable;

	virtual void BeginPlay() override;

private:



};
