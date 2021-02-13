// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMPBase/Utility/IMPInteractInterface.h"
#include "IMPInteractableBase.generated.h"

/** Abstract Interactable class to define custom default behaviour for all interactable game objects derived from this class */

UCLASS(Abstract)
class IMPBASE_API AIMPInteractableBase : public AActor, public IIMPInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIMPInteractableBase();

	/**
	 * Enables/disables a glowing outline effect around the Interactable's mesh, so that it appears to be in focus
	 * @param bInFocus - set to true to draw a glowing outline around the mesh; false will disable the outline
	 */
	void SetInFocus(const bool bInFocus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|StaticMesh")
	/** Reference to the Interactables StaticMeshComponent */
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Interaction")
	bool bUseInteractionTimeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Interaction")
	float InteractTimeSpan;

	UFUNCTION(BlueprintCallable)
	float GetInteractionTimeNormalized() const;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsReadyToInteract() const { return bReadyToInteract; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	/** A placeholder Interface event that defines what happens when interacting with the Interactable. */
	void OnInteract();
	virtual void OnInteract_Implementation();

	void OnInteractStop();
	virtual void OnInteractStop_Implementation();

	void ResetInteractionTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FTimerHandle InteractTimerHandle;

	bool bReadyToInteract;

	void SetReadyToInteract();

};
