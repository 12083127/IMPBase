// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IMPBase/IMPBase.h"
#include "IMPJournalEntryObject.generated.h"

/* A utility class for journal entries primarily needed by the GUI to spawn List-Objects and display them */
UCLASS(BlueprintType, Blueprintable)
class IMPBASE_API UIMPJournalEntryObject : public UObject
{
	GENERATED_BODY()

public:

	UIMPJournalEntryObject();

	UFUNCTION(BlueprintCallable)
	/* Sets the data that the journal entry object stores. */
	void SetJournalEntryData(const FIMPNoteEntry InNote);
	
	UFUNCTION(BlueprintCallable)
	/* @return Gets all data stored in the JournalEntryObject */
	FORCEINLINE FIMPNoteEntry GetJournalEntryData() const { return NoteEntry; }

private:

	FIMPNoteEntry NoteEntry;
};
