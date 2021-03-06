// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IMPBase/IMPBase.h"
#include "Perception/AIPerceptionTypes.h"
#include "IMPNPCCharacterBase.generated.h"


UENUM(BlueprintType)
enum class EPathingType : uint8
{
	PT_OneWay UMETA(DisplayName = "One Way"),
	PT_Looping UMETA(DisplayName = "Loop Path"),
	PT_Reverse UMETA(DisplayName = "Reverse Path")
};

UCLASS()
class IMPBASE_API AIMPNPCCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIMPNPCCharacterBase();

	// vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EPathingType PathingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EFactionType Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<class AIMPAIWaypoint*> Waypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAIPerceptionComponent* SenseComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Sight* SightSense;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	class UCharacterMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UIMPEnergyComponent* EnergyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MeleeRange;

	int32 CurrentWaypointIndex; //private?

	float SightRadius;
	float LoseSightRadius;

	// functions
	/** Enables/disables a glowing outline effect around the Interactable's mesh, so that it appears to be in focus
	 * @param bInFocus - set to true to draw a glowing outline around the mesh; false will disable the outline
	 */
	void SetInFocus(const bool bInFocus);

	void SetIsGoingForward(bool IsGoingForward);
	void SetIMPController(class AIMPNPCCharacterAIBase* InController);

	UFUNCTION(BlueprintCallable)
	void DamageNPC(float Amount, FVector HitImpulse);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<class AIMPAIWaypoint*> GetWaypoints() const { return Waypoints; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UAIPerceptionComponent* GetSensingComponent() const { return SenseComp; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EFactionType GetInitialFaction() const { return Faction_Initial; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAggroDistance() const { return AggroDistance; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsGoingForward() const { return bGoingForward; }
		
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsDead() const { return bDead; }



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// vars
	class AIMPNPCCharacterAIBase* IMPController;
	EFactionType Faction_Initial;
	bool bGoingForward;
	bool bDead;
	float AggroDistance;
	FAttributeFloat Health;

	// functions

	void KillNPC(FVector HitImpulse);

	UFUNCTION()
	void OnSensePlayerUpdate(AActor* Actor, FAIStimulus Stimulus);

};
