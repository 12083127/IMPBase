// IMP Project - Robert Lehmann 2020-2021


#include "IMPPlayerState.h"
#include "IMPBase/Components/IMPAbilitySystemComponent.h"
#include "IMPBase/Utility/IMPAttributeSetBase.h"

AIMPPlayerState::AIMPPlayerState()
{

}

void AIMPPlayerState::BeginPlay()
{
	Super::BeginPlay();

	log("Playerstate initialized!");
}

void AIMPPlayerState::AddNoteToPlayerJournal(const FIMPNoteEntry Note)
{
	if (Note.NoteID == -1)
	{
		UE_LOG(LogDataTable, Error, TEXT("Note does not exist! Please double check Note ID and reference the correct note."));
	}
	else
	{
		if (Note.NoteCategory != ENoteCategory::NC_None)
		{
			PlayerNoteJournal.AddUnique(Note);
		}
		else
		{
			UE_LOG(LogDataTable, Warning, TEXT("Note ID: %i Has a category of None. Please check the entry and set a valid category. Note has not been added"), Note.NoteID);
		}
	}
}

FIMPNoteEntry AIMPPlayerState::FindNoteEntry(const FName NoteID) const
{
	if (NoteDataTable)
	{
		FIMPNoteEntry* NoteEntry = NoteDataTable->FindRow<FIMPNoteEntry>(NoteID, "");

		if (NoteEntry)
		{
			return *NoteEntry;
		}
	}
	else
	{
		UE_LOG(LogDataTable, Error, TEXT("No Data Table Reference set inside the Player State!"));
	}

	FIMPNoteEntry EmptyEntry;

	EmptyEntry.NoteID = -1;
	EmptyEntry.NoteHeading = FText::FromString("Note Heading not found! Double check Note ID!");
	EmptyEntry.NoteBody = FText::FromString("Note Body not found! Double check Note ID!");
	EmptyEntry.NoteCategory = ENoteCategory::NC_None;

	return EmptyEntry;
}


