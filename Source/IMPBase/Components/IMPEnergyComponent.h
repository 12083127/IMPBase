// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IMPBase/IMPBase.h"
#include "IMPEnergyComponent.generated.h"

/** A component that adds Elemental Energy vars and functions to any actor it is attached to.
 *  This is done to have a centralized code base related to everything regarding Elemental Energy.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPBASE_API UIMPEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIMPEnergyComponent();


	UFUNCTION(BlueprintCallable)
	/** Modifies the maximum EnergyLevel of this entity by adding to its current maximum EnergyLevel.
	 * @param ByAmount - The value that will be added to the current maximum EnergyLevel
	 */
	void ModifyEnergyMax(const float ByAmount);

	UFUNCTION(BlueprintCallable)
	/** Sets the maximum EnergyLevel this entity can store.
	 * @param InValue - The value the maximum EnergyLevel will be set to
	 */
	void SetEnergyMax(const float InValue);

	UFUNCTION(BlueprintCallable)
	/** Modifies the EnergyLevel of this entity by adding to its current EnergyLevel.
	 * @param ByAmount - The value that will be added to the current EnergyLevel
	 */
	void ModifyCurrentEnergyLevel(const float ByAmount);

	UFUNCTION(BlueprintCallable)
	/** Sets the current EnergyLevel of this entity.
	 * @param InValue - The value EnergyLevel will be set to
	 */
	void SetCurrentEnergyLevel(const float InValue);

	UFUNCTION(BlueprintCallable)
	/** Sets the Energy Type that this entity can store.
	 * @param InType - The EnergyType that the entity will be set to inhabit
	 */
	void SetEnergyType(const EEnergyType InType);


	UFUNCTION(BlueprintCallable)
	/* Returns the type of Energy stored in this entity. */
	FORCEINLINE EEnergyType GetEnergyType() const { return EnergyType; }

	UFUNCTION(BlueprintCallable)
	/* Returns the current EnergyLevel this entity has. */
	FORCEINLINE float GetCurrentEnergyLevel() const { return EnergyLevel.Current; }

	UFUNCTION(BlueprintCallable)
	/* Returns the highest possible EnergyLevel this entity can store. */
	FORCEINLINE float GetCurrentEnergyMax() const { return EnergyLevel.Max; }

	UFUNCTION(BlueprintCallable)
	/* Returns the current EnergyLevel this entity has as a normalized value */
	FORCEINLINE float GetEnergyLevelNormalized() const { return EnergyLevel.GetNormalizedValue(); }

	UFUNCTION(BlueprintCallable)
	/* Returns whether or not the entity is an Energy-Container or an Energy-Source. */
	FORCEINLINE bool IsEnergyContainer() const { return bContainer; }

	UFUNCTION(BlueprintCallable)
	/* Returns whether or not the current EnergyLevel is equal to the maximum EnergyLevel. */
	FORCEINLINE bool IsCharged() const { return bCharged; }

	UFUNCTION(BlueprintCallable)
	/* Returns whether or not the entity can be charged with energy. */
	FORCEINLINE bool IsChargeable() const { return bChargeable; }

	UFUNCTION(BlueprintCallable)
	/* Returns whether or not the current EnergyLevel is <= 0 */
	FORCEINLINE bool IsDrained() const { return bDrained; }

	UFUNCTION(BlueprintCallable)
	/* Returns whether or not the entity can be drained for energy. */
	FORCEINLINE bool IsDrainable() const { return bDrainable; }

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	/* The Energy Type that this entity stores on spawn*/
	EEnergyType EnergyType;

	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	/* The EnergyLevel this entity has on spawn */
	float Energy;

	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	/* The maximum EnergyLevel this entity has on spawn */
	float EnergyMax;

	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	/* Whether this entity will spawn as a container or as a source. By default this is set to false which means the entity is a source. */
	bool bContainer;

	TGameAttribute<float> EnergyLevel;

	bool bCharged;
	bool bChargeable;
	bool bDrained;
	bool bDrainable;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
