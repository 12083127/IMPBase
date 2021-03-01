// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerState.h"
#include "IMPBase/IMPBase.h"
#include "IMPBase/Utility/IMPInventoryItemBase.h"
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

USTRUCT(BlueprintType)
struct FIMPInventoryItem : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	int32 ItemValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1))
	int32 ItemStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.f))
	float ItemWeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UIMPInventoryItemBase> ItemBase;

	// operator overloading to check for duplicates
	bool operator==(const FIMPInventoryItem& Item) const
	{
		if (ItemID == Item.ItemID)
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IMP Base", meta = (AllowPrivateAccess = "true"))
	/** Holds all the notes the player has found */
	TArray<class UIMPJournalEntryObject*> PlayerNoteJournal;

public:

	AIMPPlayerState();
	
	UFUNCTION(BlueprintCallable)
	/** Checks if the Note you want to add is valid and adds it to the players journal as an IMPJournalEntryObject.
	 *  @param Note - The note to be added.
	 */
	void AddNoteToPlayerJournal(const FIMPNoteEntry Note);

	UFUNCTION(BlueprintCallable)
	/** Looks for a Note Entry and returns it as a struct for later use 
	 *  @param NoteID - NoteID of the note you are looking for.
	 */
	FIMPNoteEntry FindNoteEntry(const FName NoteID) const;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<class UIMPJournalEntryObject*> GetPlayerNoteJournal() const { return PlayerNoteJournal; }

	//FORCEINLINE class UDataTable* GetNoteJournalDB() const { return NoteDataTable; }

protected:

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base")
	/** Reference to the data table that holds all note entries. NoteID and RowName in the data table need to be identical! */
	const UDataTable* NoteDataTable;

	virtual void BeginPlay() override;

private:



};
