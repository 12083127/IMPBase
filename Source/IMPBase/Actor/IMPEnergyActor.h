// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/IMPBase.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPEnergyActor.generated.h"

/**
 * 
 */
UCLASS()
class IMPBASE_API AIMPEnergyActor : public AIMPInteractableBase
{
	GENERATED_BODY()
	
public:

	AIMPEnergyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* InteractionTriggerVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UIMPEnergyComponent* EnergyComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDrainedEvent();
	virtual void OnDrainedEvent_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChargedEvent();
	virtual void OnChargedEvent_Implementation();

private:

	bool bEmptyEventDone;
	bool bChargedEventDone;
};
