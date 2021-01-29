// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "IMPBase/IMPBase.h"
#include "IMPNPCCharacterAIBase.generated.h"

/**
 * 
 */
UCLASS()
class IMPBASE_API AIMPNPCCharacterAIBase : public AAIController
{
	GENERATED_BODY()

public:

	AIMPNPCCharacterAIBase();

		// vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlackboardComponent* BlackboardComp;

	// functions
	void SetCanSeePlayer(bool CanSeePlayer);
	void SetTargetLocation(FVector NewLocation);
	void SetPlayerLocation(FVector NewLocation);
	void SetWithinAggroDistance(bool WithinAggroDistance);
	void SetWithinMeleeRange(bool WithinMeleeRange);
	void SetIsPlayerDead(bool IsPlayerDead);

	UFUNCTION(BlueprintCallable)
	void SetFactionKey(EFactionType NewFaction);

	UFUNCTION(BlueprintCallable)
	void ResetFaction(class AIMPNPCCharacterBase* NPC);

protected:
	virtual void BeginPlay() override;

private:

	// vars
	FName BKCanSeePlayer;
	FName BKTargetLocation;
	FName BKPlayerLocation;
	FName BKFaction;
	FName BKWithinAggroDistance;
	FName BKWithinMeleeRange;
	FName BKIsPlayerDead;

	bool bCanSeePlayer;
	bool bPlayerDead;
	bool bWithinAggroDistance;
	bool bWithinMeleeRange;
	FVector TargetLocation;
	FVector PlayerLocation;
	EFactionType Faction;

	class AIMPPlayer* Player;
	class AIMPNPCCharacterBase* ControlledPawn;

	// functions
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	float GetDistance(AActor* FromActor, AActor* ToActor);
};
