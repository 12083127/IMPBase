// IMP Project - Robert Lehmann 2020-2021


#include "IMPBTTRunFromPlayer.h"

#include "IMPBase/AI/IMPNPCCharacterBase.h"
#include "IMPBase/AI/IMPNPCCharacterAIBase.h"
#include "IMPBase/Player/IMPPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISenseConfig_Sight.h"


EBTNodeResult::Type UIMPBTTRunFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIMPNPCCharacterAIBase* IMPController = Cast<AIMPNPCCharacterAIBase>(OwnerComp.GetAIOwner());

	if (IMPController)
	{
		AIMPNPCCharacterBase* NPC = Cast<AIMPNPCCharacterBase>(IMPController->GetPawn());
		AIMPPlayer* Player = Cast<AIMPPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (NPC && Player)
		{
			FVector PlayerLoc = Player->GetActorLocation();
			FVector NPCLoc = NPC->GetActorLocation();
			FVector V = NPCLoc - PlayerLoc;
			float DistanceToPlayer = V.Size();

			FVector FleeingPoint = NPCLoc + V.GetSafeNormal() * (NPC->LoseSightRadius - DistanceToPlayer);

			IMPController->MoveToLocation(FleeingPoint);

			return EBTNodeResult::Succeeded;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
