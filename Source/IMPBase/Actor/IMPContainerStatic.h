// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPContainerBase.h"
#include "IMPContainerStatic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class IMPBASE_API AIMPContainerStatic : public AIMPContainerBase
{
	GENERATED_BODY()
	
public:

	AIMPContainerStatic();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base")
	/* Reference to the Interactables StaticMeshComponent */
	class UStaticMeshComponent* Mesh;

	void OnInteract(APawn* Caller);
	virtual void OnInteract_Implementation(APawn* Caller);

	virtual void SetInFocus(const bool bInFocus) override;

protected:

private:
};
