// IMP Project - Robert Lehmann 2020-2021


#include "IMPBTTFindNextWaypoint.h"

#include "IMPBase/AI/IMPNPCCharacterAIBase.h"
#include "IMPBase/AI/IMPNPCCharacterBase.h"
#include "IMPBase/AI/IMPAIWaypoint.h"

EBTNodeResult::Type UIMPBTTFindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AIMPNPCCharacterAIBase* IMPController = Cast<AIMPNPCCharacterAIBase>(OwnerComp.GetAIOwner());

    if (IMPController)
    {
        AIMPNPCCharacterBase* NPC = Cast<AIMPNPCCharacterBase>(IMPController->GetPawn());

        if (NPC)
        {
            TArray<AIMPAIWaypoint*> Waypoints = NPC->GetWaypoints();

            if (Waypoints.Num() == 0)
            {
                return EBTNodeResult::Failed;
            }

            AIMPAIWaypoint* NextWaypoint = nullptr;

            // get pathing type from NPC
            switch (NPC->PathingType)
            {
                // moves along the waypoint chain and stops at the end
            case EPathingType::PT_OneWay:
                if (NPC->CurrentWaypointIndex < Waypoints.Num() - 1)
                {
                    NPC->CurrentWaypointIndex++;
                }
                else // stop at last waypoint
                {
                    NextWaypoint = Waypoints.Last();
                    return EBTNodeResult::Succeeded;
                }
                break;

                // moves along the waypoint chain and then loops back to the first waypoint
            case EPathingType::PT_Looping:
                if (NPC->CurrentWaypointIndex < Waypoints.Num() - 1)
                {
                    NPC->CurrentWaypointIndex++;
                }
                else // loop to first waypoint on last waypoint
                {
                    NPC->CurrentWaypointIndex = 0;
                }
                break;

                // moves along the waypoint chain, then reverses the path traveled
            case EPathingType::PT_Reverse:
                // increment the index if we are going forward
                if (NPC->IsGoingForward())
                {
                    if (NPC->CurrentWaypointIndex < Waypoints.Num() - 1)
                    {
                        NPC->CurrentWaypointIndex++;
                    }
                    else
                    {
                        NPC->SetIsGoingForward(false);
                        NPC->CurrentWaypointIndex--;
                    }
                }
                else // decrement the index to reverse direction
                {
                    if (NPC->CurrentWaypointIndex > 0)
                    {
                        NPC->CurrentWaypointIndex--;
                    }
                    else
                    {
                        NPC->SetIsGoingForward(true);
                        NPC->CurrentWaypointIndex++;
                    }
                }

                break;
            default: break;
            }

            NextWaypoint = Waypoints[NPC->CurrentWaypointIndex];

            // pass the newly found waypoint to the AI Controller
            if (NextWaypoint)
            {
                IMPController->SetTargetLocation(NextWaypoint->GetActorLocation());
            }
            else // abort task
            {
                return EBTNodeResult::Failed;
            }

            return EBTNodeResult::Succeeded;
        }
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}
