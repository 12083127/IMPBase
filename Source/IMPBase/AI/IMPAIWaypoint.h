// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMPAIWaypoint.generated.h"

UENUM(BlueprintType)
enum class EWaypointType : uint8
{
	WT_Passing UMETA(DisplayName = "Passing"),
	WT_Roaming UMETA(DisplayName = "Roaming"),
	WT_Guarding UMETA(DisplayName = "Guarding")
};

UCLASS()
class IMPBASE_API AIMPAIWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIMPAIWaypoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWaypointType WaypointType;

	FORCEINLINE float GetDuration() const { return Duration; }
	FORCEINLINE EWaypointType GetWaypointType() const { return WaypointType; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class UBillboardComponent* EDSprite;
};
