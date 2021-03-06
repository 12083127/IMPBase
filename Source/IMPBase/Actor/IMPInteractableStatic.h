// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPInteractableStatic.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class IMPBASE_API AIMPInteractableStatic : public AIMPInteractableBase
{
	GENERATED_BODY()

public:

	AIMPInteractableStatic();

	/** Enables/disables a glowing outline effect around the Interactable's mesh, so that it appears to be in focus
	 * @param bInFocus - set to true to draw a glowing outline around the mesh; false will disable the outline
	 */
	virtual void SetInFocus(const bool bInFocus) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base")
	/* Reference to the Interactables StaticMeshComponent */
	class UStaticMeshComponent* Mesh;
};
