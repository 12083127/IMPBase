// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPInteractableAnimated.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class IMPBASE_API AIMPInteractableAnimated : public AIMPInteractableBase
{
	GENERATED_BODY()

public:
	
	AIMPInteractableAnimated();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	/* Reference to the Interactables SkeletalMeshComponent. */
	class USkeletalMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
	/*The state will flip flop between true and false by default when interacting with the object. Use this to override the Interactables activation behaviour. */
	void SetInteractableState(const bool bState);

	void OnInteract(APawn* Caller);
	virtual void OnInteract_Implementation(APawn* Caller);

	virtual void SetInFocus(const bool bInFocus) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IMP Base|Deactivate", meta = (DisplayAfter="ActivateSound"))
	/* Sound that plays upon deactivating the object. */
	class USoundBase* DeactivateSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IMP Base|Activate")
	/* Animation that plays upon activating the object. If you do not want to use a Deactivate Animation, make sure that the Activate Animation is designed to loop. */
	class UAnimationAsset* ActivateAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IMP Base|Deactivate", meta = (DisplayAfter="ActivateAnimation"))
	/* Animation that plays upon deactivating the object. */
	class UAnimationAsset* DeactivateAnimation;

	bool bInteractableState;

	bool PlayInteractionAnim(class UAnimationAsset* const Anim);

private:
};
