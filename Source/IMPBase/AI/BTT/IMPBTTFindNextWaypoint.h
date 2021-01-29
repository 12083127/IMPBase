// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "IMPBTTFindNextWaypoint.generated.h"

/** Behaviour Tree Task that handles the AI's logic for picking the next patrolling waypoint. */
UCLASS()
class IMPBASE_API UIMPBTTFindNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
