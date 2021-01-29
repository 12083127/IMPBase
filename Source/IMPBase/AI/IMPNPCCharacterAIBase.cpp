// IMP Project - Robert Lehmann 2020-2021


#include "IMPNPCCharacterAIBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "IMPBase/AI/IMPNPCCharacterBase.h"
#include "IMPBase/Player/IMPPlayer.h"
#include "Kismet/GameplayStatics.h"

AIMPNPCCharacterAIBase::AIMPNPCCharacterAIBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviourTree"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	bCanSeePlayer = false;
	bWithinAggroDistance = false;
	bWithinMeleeRange = false;
	bPlayerDead = false;

	BKCanSeePlayer = "CanSeePlayer";
	BKTargetLocation = "TargetLocation";
	BKPlayerLocation = "PlayerLocation";
	BKFaction = "Faction";
	BKWithinAggroDistance = "WithinAggroDistance";
	BKWithinMeleeRange = "WithinMeleeRange";
	BKIsPlayerDead = "IsPlayerDead";
}

void AIMPNPCCharacterAIBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AIMPPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AIMPNPCCharacterAIBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// init Blackboard + keys and Behaviortree if available
	AIMPNPCCharacterBase* NPC = Cast<AIMPNPCCharacterBase>(InPawn);

	if (NPC && BehaviorTree)
	{
		ControlledPawn = NPC;
		NPC->SetIMPController(this);

		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));

		SetCanSeePlayer(bCanSeePlayer);
		SetWithinAggroDistance(bWithinAggroDistance);
		SetWithinMeleeRange(bWithinMeleeRange);
		SetIsPlayerDead(bPlayerDead);
		SetTargetLocation(TargetLocation);
		SetPlayerLocation(PlayerLocation);
		SetFactionKey(ControlledPawn->Faction);

		RunBehaviorTree(BehaviorTree);
	}
}

void AIMPNPCCharacterAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ControlledPawn->IsDead())
	{
		return;
	}

	// update blackboard keys
	if (Player && ControlledPawn)
	{
		SetPlayerLocation(Player->GetActorLocation());
		SetWithinAggroDistance(GetDistance(ControlledPawn, Player) < ControlledPawn->GetAggroDistance());
		SetWithinMeleeRange(GetDistance(ControlledPawn, Player) < ControlledPawn->MeleeRange);
		SetIsPlayerDead(Player->IsDead());

		if (Player->IsDead())
		{
			SetCanSeePlayer(false);
		}
	}
}

void AIMPNPCCharacterAIBase::SetCanSeePlayer(bool CanSeePlayer)
{
	bCanSeePlayer = CanSeePlayer;
	BlackboardComp->SetValueAsBool(BKCanSeePlayer, bCanSeePlayer);
}

void AIMPNPCCharacterAIBase::SetTargetLocation(FVector NewLocation)
{
	TargetLocation = NewLocation;
	BlackboardComp->SetValueAsVector(BKTargetLocation, TargetLocation);
}

void AIMPNPCCharacterAIBase::SetPlayerLocation(FVector NewLocation)
{
	PlayerLocation = NewLocation;
	BlackboardComp->SetValueAsVector(BKPlayerLocation, PlayerLocation);
}

void AIMPNPCCharacterAIBase::SetWithinAggroDistance(bool WithinAggroDistance)
{
	bWithinAggroDistance = WithinAggroDistance;
	BlackboardComp->SetValueAsBool(BKWithinAggroDistance, bWithinAggroDistance);
}

void AIMPNPCCharacterAIBase::SetWithinMeleeRange(bool WithinMeleeRange)
{
	bWithinMeleeRange = WithinMeleeRange;
	BlackboardComp->SetValueAsBool(BKWithinMeleeRange, bWithinMeleeRange);
}

void AIMPNPCCharacterAIBase::SetIsPlayerDead(bool IsPlayerDead)
{
	bPlayerDead = IsPlayerDead;
	BlackboardComp->SetValueAsBool(BKIsPlayerDead, bPlayerDead);
}

void AIMPNPCCharacterAIBase::SetFactionKey(EFactionType NewFaction)
{
	Faction = NewFaction;
	BlackboardComp->SetValueAsEnum(BKFaction, (uint8)Faction);
}

void AIMPNPCCharacterAIBase::ResetFaction(AIMPNPCCharacterBase* NPC)
{
	SetFactionKey(NPC->GetInitialFaction());
}

float AIMPNPCCharacterAIBase::GetDistance(AActor* FromActor, AActor* ToActor)
{	
	if (FromActor && ToActor)
	{
		FVector FromLoc, ToLoc;

		FromLoc = FromActor->GetActorLocation();
		ToLoc = ToActor->GetActorLocation();

		return FVector::Dist(FromLoc, ToLoc);
	}

	return 0.f;
}
