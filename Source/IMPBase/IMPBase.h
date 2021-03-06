// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "IMPBase.generated.h"

// project macros
#define print(color, text)								if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, color, TEXT(text), false)
#define printc(channel, color, text)					if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, color, TEXT(text))
#define printf(color, format, ...)						if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, color, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcf(channel, color, format, ...)			if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, color, FString::Printf(TEXT(format), ##__VA_ARGS__))
#define printfloat(color, variable)						if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, color, FString::Printf(TEXT(#variable ": %f"), variable), false)
#define printcfloat(channel, color, variable)			if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, color, FString::Printf(TEXT(#variable ": %f"), variable))

#define printvector(color, variable)					if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, color, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()), false)
#define printcvector(channel, color, variable)			if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, color, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()))

#define log(text)										UE_LOG(LogTemp, Warning, TEXT(text));
#define logstring(text, string)							UE_LOG(LogTemp, Warning, TEXT(text " %s"), string);

#define ECC_Focusable									ECC_GameTraceChannel1
#define ECC_Shootable									ECC_GameTraceChannel2

UENUM(BlueprintType)
/* Ability Input IDs used by GAS */
enum class EIMPAbilityInputID : uint8
{
	AI_None,
	AI_Confirm,
	AI_Cancel,
	AI_Sprint UMETA(DisplayName = "Sprint"),
	AI_Drain UMETA(DisplayName = "Drain"),
};

UENUM(BlueprintType)
/* All energy types for the energy gameplay mechanic */
enum class EEnergyType : uint8
{
	ET_None UMETA(DisplayName = "None"),
	ET_Electric UMETA(DisplayName = "Electric"),
	ET_Fire UMETA(DisplayName = "Fire"),
	ET_Water UMETA(DisplayName = "Water"),
};

UENUM(BlueprintType) 
/* rename to ENPCBehavior; possible move to IMPEnemyNPC.h? */
enum class EFactionType : uint8
{
	FT_None UMETA(DisplayName = "None"),
	FT_Enemy UMETA(DisplayName = "Enemy"),
	FT_Neutral UMETA(DisplayName = "Neutral"),
	FT_Friendly UMETA(DisplayName = "Friendly")
};

UENUM(BlueprintType)
/* Note categories for the player journal. Notes of category "None" will not be added to the journal if picked up! */
enum class ENoteCategory : uint8
{
	NC_None UMETA(DisplayName = "None"),
	NC_Story UMETA(DisplayName = "Story"),
	NC_Treasure UMETA(DisplayName = "Treasure"),
	NC_Mystery UMETA(DisplayName = "Mystery")
};

USTRUCT(BlueprintType)
/* Structure that holds all necessary data for every journal entry the player can find */
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

/** Templated structure providing a variable with a Max and a Current value and some utility functions. 
* Useful for every attribute that is set using a max value and a current value clamped on max. e.g. Health... 
*/
template <typename T>
struct TGameAttribute
{
	T Current;
	T Max;

	float GetNormalizedValue() const
	{
		if ((float)Max == 0.f)
		{
			return 0.f;
		}
		else
		{
			return (float)(Current / Max);
		}
	}

	void Modify(T ByAmount)
	{
		Current += ByAmount;
		Current = FMath::Clamp(Current, (T)0, Max);
	}

	void Set(T InValue)
	{
		Current = InValue;
		Current = FMath::Clamp(Current, (T)0, Max);
	}

	void Initialize(T InMax, T InCurrent)
	{
		Max = InMax;
		Current = InCurrent;

		Current = FMath::Clamp(Current, (T)0, Max);
	}
};

/* DEPRECATED: replace with TGameAttribute! */
struct FAttributeFloat
{
	float Current;
	float Max;

	const float GetNormalizedValue()
	{
		if (Max == 0.f)
		{
			return 0.f;
		}
		else
		{
			return Current / Max;
		}
	}

	void Modify(float amount)
	{
		Current += amount;
		Current = FMath::Clamp(Current, 0.f, Max);
	}
};

/* DEPRECATED: replace with TGameAttribute! */
struct FAttributeInt
{
	int32 Current;
	int32 Max;

	const float GetNormalizedValue()
	{
		if (Max == 0)
		{
			return 0.f;
		}
		else
		{
			return (float)Current / Max;
		}
	}

	void Modify(int32 amount)
	{
		Current += amount;
		Current = FMath::Clamp(Current, 0, Max);
	}
};
