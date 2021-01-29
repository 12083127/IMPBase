// IMP Project - Robert Lehmann 2020-2021


#include "IMPAIWaypoint.h"
#include "Components/BillboardComponent.h"

// Sets default values
AIMPAIWaypoint::AIMPAIWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// set editor sprite
	EDSprite = CreateDefaultSubobject<UBillboardComponent>(TEXT("Editor Sprite"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> spriteLookUp(TEXT("/Engine/EditorMaterials/TargetIcon"));

	if (spriteLookUp.Succeeded())
	{
		EDSprite->SetSprite(spriteLookUp.Object);
		EDSprite->SetEditorScale(0.5f);
		EDSprite->SetupAttachment(RootComponent);
	}

	// set default attributes
	Duration = 2.f;
	WaypointType = EWaypointType::WT_Passing;
}

// Called when the game starts or when spawned
void AIMPAIWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}


