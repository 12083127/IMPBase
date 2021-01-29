// IMP Project - Robert Lehmann 2020-2021


#include "IMPPlayerState.h"
#include "IMPBase/Components/IMPAbilitySystemComponent.h"
#include "IMPBase/Utility/IMPAttributeSetBase.h"

AIMPPlayerState::AIMPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UIMPAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(false);

	AttributeSet = CreateDefaultSubobject<UIMPAttributeSetBase>(TEXT("AttributeSet"));
}

void AIMPPlayerState::AddNoteEntry(FName RowName)
{
	if (NoteJournalData)
	{
		FIMPNoteEntry* Note = NoteJournalData->FindRow<FIMPNoteEntry>(RowName, "");

		if (Note)
		{
			NotesJournal.AddUnique(*Note);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to add new entry! Note probably doesn't exist."));
		}
	}
}

FIMPNoteEntry AIMPPlayerState::GetNoteEntry(const FName NoteID) const
{
	FIMPNoteEntry* NoteEntry = NoteJournalData->FindRow<FIMPNoteEntry>(NoteID, "");

	if (NoteEntry)
	{
		return *NoteEntry;
	}
	else
	{
		FIMPNoteEntry EmptyEntry;
		EmptyEntry.NoteID = 99999;
		EmptyEntry.NoteHeading = FText::FromString("Note Heading not found! Double check Note ID!");
		EmptyEntry.NoteBody = FText::FromString("Note Body not found! Double check Note ID!");
		EmptyEntry.NoteCategory = ENoteCategory::NC_None;

		return EmptyEntry;
	}
}

UAbilitySystemComponent* AIMPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
