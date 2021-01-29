// IMP Project - Robert Lehmann 2020-2021


#include "IMPNPCCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IMPBase/AI/IMPAIWaypoint.h"
#include "IMPBase/AI/IMPNPCCharacterAIBase.h"
#include "IMPBase/Components/IMPEnergyComponent.h"
#include "IMPBase/Player/IMPPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AIMPNPCCharacterBase::AIMPNPCCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// get existing movement comp and set movement defaults
	MovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());

	if (MovementComp)
	{
		FRotator RotSpeed = FRotator(0.f, 250.f, 0.f);
		MovementComp->bUseControllerDesiredRotation = true;
		MovementComp->RotationRate = RotSpeed;
	}

	SenseComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SensingComponent"));

	if (SenseComp)
	{
		SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

		SightRadius = 750.f;
		LoseSightRadius = SightRadius * 1.25f;

		SightSense->SightRadius = SightRadius;
		SightSense->LoseSightRadius = LoseSightRadius;
		SightSense->SetMaxAge(10.f);

		AggroDistance = SightRadius * 0.75f;

		SightSense->DetectionByAffiliation.bDetectEnemies = true;
		SightSense->DetectionByAffiliation.bDetectNeutrals = true;
		SightSense->DetectionByAffiliation.bDetectFriendlies = true;

		SenseComp->ConfigureSense(*SightSense);

		SenseComp->OnTargetPerceptionUpdated.AddDynamic(this, &AIMPNPCCharacterBase::OnSensePlayerUpdate);
	}

	EnergyComponent = CreateDefaultSubobject<UIMPEnergyComponent>(FName(TEXT("EnergyComponent")));

	// set default attributes
	PathingType = EPathingType::PT_Looping;
	Faction = EFactionType::FT_None;

	CurrentWaypointIndex = 0;
	bGoingForward = true;
	MeleeRange = 300.f;

	Health.Max = 100.f;
	Health.Current = Health.Max;

	bDead = false;
}

// Called when the game starts or when spawned
void AIMPNPCCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (Waypoints.Num() == 0)
	{
		Waypoints.Add(GetWorld()->SpawnActor<AIMPAIWaypoint>(GetActorLocation(), FRotator()));
	}

	Faction_Initial = Faction;
}

void AIMPNPCCharacterBase::SetInFocus(bool bInFocus)
{
	GetMesh()->SetRenderCustomDepth(bInFocus);
}

void AIMPNPCCharacterBase::SetIsGoingForward(bool IsGoingForward)
{
	bGoingForward = IsGoingForward;
}

void AIMPNPCCharacterBase::SetIMPController(AIMPNPCCharacterAIBase* InController)
{
	IMPController = InController;
}

void AIMPNPCCharacterBase::DamageNPC(float Amount, FVector HitImpulse)
{
	if (!bDead && IMPController)
	{
		Health.Modify(-Amount);
		IMPController->SetCanSeePlayer(true);

		if (Health.Current <= 0.f)
		{
			KillNPC(HitImpulse);
		}
	}
}

void AIMPNPCCharacterBase::KillNPC(FVector HitImpulse)
{
	bDead = true;

	if (Controller)
	{
		Controller->StopMovement();
		Controller->UnPossess();
	}

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddForceToAllBodiesBelow(HitImpulse * GetMesh()->GetBodyInstance()->GetBodyMass() * 600.f);
	GetMesh()->AddImpulseToAllBodiesBelow(HitImpulse * GetMesh()->GetBodyInstance()->GetBodyMass() * 600.f);
	//GetMesh()->SetPhysicsLinearVelocity(hitImpulse);

	UCapsuleComponent* collComp = GetCapsuleComponent();

	if (collComp)
	{
		collComp->SetCollisionProfileName("NoCollision", false);
	}
}

void AIMPNPCCharacterBase::OnSensePlayerUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (IMPController)
	{
		AIMPPlayer* Player = Cast<AIMPPlayer>(Actor);

		if (Player)
		{
			IMPController->SetCanSeePlayer(Stimulus.WasSuccessfullySensed());
		}
	}
}

