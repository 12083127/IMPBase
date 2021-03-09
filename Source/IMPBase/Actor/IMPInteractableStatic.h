// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPInteractableStatic.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class IMPBASE_API AIMPInteractableStatic : public AIMPInteractableBase
{
	GENERATED_BODY()

public:

	AIMPInteractableStatic();

	virtual void SetInFocus(const bool bInFocus) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base")
	/* Reference to the Interactables StaticMeshComponent */
	class UStaticMeshComponent* Mesh;

	void OnInteract(APawn* Caller);
	virtual void OnInteract_Implementation(APawn* Caller);

protected:

	virtual void BeginPlay() override;

private:
};
