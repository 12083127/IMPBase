// IMP Project - Robert Lehmann 2020-2021


#include "IMPPickupFloating.h"

AIMPPickupFloating::AIMPPickupFloating()
{
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 100.f;
	ZBoppinRange = 15.f;
}

void AIMPPickupFloating::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rot = Mesh->GetComponentRotation();
	Rot.Yaw += RotationSpeed * DeltaTime;

	float RunningTime = GetGameTimeSinceCreation();

	FVector ZLoc = GetActorLocation();
	ZLoc.Z += FMath::Sin(RunningTime + DeltaTime) * ZBoppinRange * DeltaTime;

	SetActorRelativeLocation(ZLoc);
	Mesh->SetRelativeRotation(Rot);
}
