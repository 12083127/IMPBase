// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilitySystemInterface.h"
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
class IMPBASE_API AIMPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AIMPPlayerState();
	

	UPROPERTY(VisibleAnywhere, Category = "IMPBase|Player")
	TArray<FIMPNoteEntry> NotesJournal;

	UFUNCTION(BlueprintCallable)
	void AddNoteEntry(FName RowName);

	UFUNCTION(BlueprintCallable)
	FIMPNoteEntry GetNoteEntry(const FName NoteID) const;

	FORCEINLINE class UDataTable* GetNoteJournalDatabase() const { return NoteJournalData; }

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "IMP Base|IMP Player State|Note Journal Data")
	class UDataTable* NoteJournalData;
	
	UPROPERTY(EditAnywhere)
	class UIMPAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere)
	class UIMPAttributeSetBase* AttributeSet;
};
