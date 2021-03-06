// IMP Project - Robert Lehmann 2020-2021


#include "IMPPreviewCaptureBase.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "IMPBase/Utility/IMPInventoryItemBase.h"

// Sets default values
AIMPPreviewCaptureBase::AIMPPreviewCaptureBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PreviewFrame = CreateDefaultSubobject<UBoxComponent>(TEXT("PreviewFrame"));
	PreviewFrame->SetBoxExtent(FVector(48.f, 48.f, 48.f));
	PreviewFrame->SetGenerateOverlapEvents(false);
	PreviewFrame->SetCollisionProfileName("NoCollision", false);
	PreviewFrame->Mobility = EComponentMobility::Static;
	RootComponent = Cast<USceneComponent>(PreviewFrame);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 160.f;
	CameraBoom->SetupAttachment(RootComponent);

	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	CaptureComponent->bCaptureEveryFrame = false;
	CaptureComponent->SetTickableWhenPaused(true);
	CaptureComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	RotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationPivot"));
	RotationPivot->SetupAttachment(RootComponent);

	IdleRotationSpeed = 5.f;

	bUseIdleRotation = true;
	
	bUserRotation = false;
	bIdleRotationActive = false;
}

void AIMPPreviewCaptureBase::UpdatePreviewMesh_Implementation(UIMPInventoryItemBase* ActiveItem)
{
}

// Called when the game starts or when spawned
void AIMPPreviewCaptureBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIMPPreviewCaptureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bUseIdleRotation)
	{
		return;
	}
	else
	{
		bool CapturingPreview = CaptureComponent->bCaptureEveryFrame;

		if (!CapturingPreview)
		{
			return;
		}
		else
		{
			if (bIdleRotationActive && !bUserRotation)
			{
				const FRotator Rot = RotationPivot->GetRelativeRotation();
				const FRotator NewRot = FRotator(Rot.Pitch, Rot.Yaw + IdleRotationSpeed * DeltaTime, Rot.Roll);

				RotationPivot->SetRelativeRotation(NewRot);
			}
		}
	}
}

float AIMPPreviewCaptureBase::GetPreviewFrameExtends() const
{
	return PreviewFrame->GetScaledBoxExtent().X;
}

void AIMPPreviewCaptureBase::SetCapturePreview(const bool bCapturePreview)
{
	if (CaptureComponent->TextureTarget != nullptr)
	{
		CaptureComponent->bCaptureEveryFrame = bCapturePreview;
	}
	else
	{
		CaptureComponent->bCaptureEveryFrame = false;
		UE_LOG(LogTemp, Error, TEXT("%s: Invalid RenderTarget Texture. Please assign a valid RenderTarget. Capture set to false."), *GetName());
	}
}

void AIMPPreviewCaptureBase::RotateMeshPreview(FVector2D InMouseLocation)
{
	if (bUserRotation)
	{
		const FVector2D ScreenLoc = InMouseLocation - MouseLocation;
		const FRotator NewRot = FRotator(ScreenLoc.Y, ScreenLoc.X * -1.f, 0.f);

		RotationPivot->AddRelativeRotation(NewRot);

		MouseLocation = InMouseLocation;
	}
}

void AIMPPreviewCaptureBase::SetUserRotation(const bool bEnabled, const FVector2D MouseLocationStart)
{
	if (bEnabled)
	{
		MouseLocation = MouseLocationStart;
	}
	
	bUserRotation = bEnabled;
}

void AIMPPreviewCaptureBase::SetIdleRotationActive(const bool bEnabled)
{
	bIdleRotationActive = bEnabled;
}

