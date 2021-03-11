// IMP Project - Robert Lehmann 2020-2021


#include "IMPPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "IMPBase/Player/IMPPlayer.h"
#include "IMPBase/UI/IMPHUD.h"
#include "IMPBase/Utility/IMPJournalEntryObject.h"

const FName AIMPPlayerController::CharMenuBinding("CharMenu");
const FName AIMPPlayerController::GameMenuBinding("GameMenu");

AIMPPlayerController::AIMPPlayerController()
{
	ActiveContainerRef = nullptr;
}

void AIMPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerHUD = Cast<AIMPHUD>(GetHUD());

	if (PlayerHUD)
	{
		PlayerHUD->ShowPlayerHUD();
	}
}

void AIMPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(CharMenuBinding, IE_Pressed, this, &AIMPPlayerController::TogglePlayerMenu).bExecuteWhenPaused = true;
	InputComponent->BindAction(GameMenuBinding, IE_Pressed, this, &AIMPPlayerController::ToggleGameMenu).bExecuteWhenPaused = true;
}

void AIMPPlayerController::TogglePlayerMenu()
{
	if (PlayerHUD)
	{
		PlayerHUD->TogglePlayerMenu();
	}
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

void AIMPPlayerController::ToggleGameMenu()
{
	if (PlayerHUD)
	{
		PlayerHUD->ToggleGameMenu();
	}
}

void AIMPPlayerController::QuitGame()
{
	this->ConsoleCommand("quit");
}

void AIMPPlayerController::ShowContainerScreen(AIMPContainerBase* const Container)
{
	if (PlayerHUD)
	{
		ActiveContainerRef = Container;
		PlayerHUD->ShowContainerScreen();
	}
}

void AIMPPlayerController::HideContainerScreen()
{
	if (PlayerHUD)
	{
		ActiveContainerRef = nullptr;
		PlayerHUD->HideContainerScreen();
	}
}

UUserWidget* AIMPPlayerController::GetContainerScreen() const
{
	if (PlayerHUD)
	{
		return PlayerHUD->GetContainerScreen();
	}

	return nullptr;
}