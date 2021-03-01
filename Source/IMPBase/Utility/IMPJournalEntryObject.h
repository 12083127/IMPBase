// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IMPBase/Player/IMPPlayerState.h"
#include "IMPJournalEntryObject.generated.h"

/* A utility class for journal entries primarily needed by the GUI to spawn List-Objects and display them */
UCLASS(Abstract, BlueprintType, Blueprintable)
class IMPBASE_API UIMPJournalEntryObject : public UObject
{
	GENERATED_BODY()

public:

	UIMPJournalEntryObject();

	UFUNCTION(BlueprintCallable)
	void SetNoteEntryData(const FIMPNoteEntry InNote);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FIMPNoteEntry GetNoteEntry() const { return NoteEntry; }

private:

	FIMPNoteEntry NoteEntry;
};
