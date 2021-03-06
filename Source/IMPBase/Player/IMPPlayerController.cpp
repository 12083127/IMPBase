// IMP Project - Robert Lehmann 2020-2021


#include "IMPPlayerController.h"
#include "IMPBase/Utility/IMPJournalEntryObject.h"

AIMPPlayerController::AIMPPlayerController()
{

}

bool AIMPPlayerController::AddNewJournalEntry(const FIMPNoteEntry Note)
{
	if (Note.NoteCategory != ENoteCategory::NC_None)
	{
		UIMPJournalEntryObject* JournalEntry = NewObject<UIMPJournalEntryObject>();
		JournalEntry->SetJournalEntryData(Note);
	
		PlayerNoteJournal.AddUnique(JournalEntry);
	
		return true;
	}
	else
	{
		UE_LOG(LogDataTable, Warning, TEXT("Note ID: %i Has a category of None. Please check the entry and set a valid category. Note has not been added"), Note.NoteID);
		return false;
	}
}
