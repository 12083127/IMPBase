// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "IMPBTTRunFromPlayer.generated.h"

/** Behaviour Tree Task that handles AI logic responsible for evading the player */
UCLASS()
class IMPBASE_API UIMPBTTRunFromPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
