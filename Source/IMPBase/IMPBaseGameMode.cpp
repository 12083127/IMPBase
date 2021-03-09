// Copyright Epic Games, Inc. All Rights Reserved.

#include "IMPBaseGameMode.h"
#include "IMPBase/Actor/IMPPreviewCaptureBase.h"
#include "UObject/ConstructorHelpers.h"

AIMPBaseGameMode::AIMPBaseGameMode()
{

}

bool AIMPBaseGameMode::GetNoteEntryFromDB(const FName NoteID, FIMPNoteEntry& OutEntry)
{
	if (NoteDataTable)
	{
		const FIMPNoteEntry* NoteEntry = NoteDataTable->FindRow<FIMPNoteEntry>(NoteID, "");

		if (NoteEntry)
		{
			OutEntry = *NoteEntry;
			return true;
		}

		return false;
	}
	else
	{
		UE_LOG(LogDataTable, Error, TEXT("No Data Table Reference set inside the Player State!"));
		return false;
	}
}

void AIMPBaseGameMode::SetItemPreviewActor(AIMPPreviewCaptureBase* PreviewActor)
{
	ItemPreviewActor = PreviewActor;
}

void AIMPBaseGameMode::SetPlayerPreviewActor(AIMPPreviewCaptureBase* PreviewActor)
{
	PlayerPreviewActor = PreviewActor;
}

bool AIMPBaseGameMode::SetGamePaused(const bool bPauseGame)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		return PC->SetPause(bPauseGame);
	}

	return false;
}
