// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMPBase/Utility/IMPInteractInterface.h"
#include "IMPInteractableBase.generated.h"

/* Abstract Interactable class to defines custom default behaviour for all interactable game objects derived from this class */
UCLASS(Abstract, NotBlueprintable)
class IMPBASE_API AIMPInteractableBase : public AActor, public IIMPInteractInterface
{
	GENERATED_BODY()
	
public:	

	AIMPInteractableBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* Exposed name of the interactable object. */
	FText DisplayName;

	/** Enables/disables a glowing outline effect around the Interactable's mesh, so that it appears to be in focus
	* @param bInFocus - set to true to draw a glowing outline around the mesh; false will disable the outline
	*/
	virtual void SetInFocus(const bool bInFocus);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteract(APawn* Caller);
	virtual void OnInteract_Implementation(APawn* Caller);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IMP Base|Activate")
	/* Sound that plays upon activating the object. */
	class USoundBase* ActivateSound;

	bool PlayInteractionSound(class USoundBase* const Sound);

	UPROPERTY()
	class UAudioComponent* AudioComponent;

private:



};
