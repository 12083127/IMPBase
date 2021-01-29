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

	/**
	* Modifies the maximum EnergyLevel of this entity by adding to its current maximum EnergyLevel.
	* @param ByAmount - The value that will be added to the current maximum EnergyLevel
	*/
	UFUNCTION(BlueprintCallable)
	void ModifyEnergyMax(const float ByAmount);

	/**
	 * Sets the maximum EnergyLevel this entity can store.
	 * @param InValue - The value the maximum EnergyLevel will be set to
	 */
	UFUNCTION(BlueprintCallable)
	void SetEnergyMax(const float InValue);

	/**
	 * Modifies the EnergyLevel of this entity by adding to its current EnergyLevel.
	 * @param ByAmount - The value that will be added to the current EnergyLevel
	 */
	UFUNCTION(BlueprintCallable)
	void ModifyCurrentEnergyLevel(const float ByAmount);

	/**
	 * Sets the current EnergyLevel of this entity.
	 * @param InValue - The value EnergyLevel will be set to
	 */
	UFUNCTION(BlueprintCallable)
	void SetCurrentEnergyLevel(const float InValue);

	/**
	 * Sets the Energy Type that this entity can store.
	 * @param InType - The EnergyType that the entity will be set to inhabit
	 */
	UFUNCTION(BlueprintCallable)
	void SetEnergyType(const EEnergyType InType);


	UFUNCTION(BlueprintCallable)
	/** Returns the type of Energy stored in this entity. */
	FORCEINLINE EEnergyType GetEnergyType() const { return EnergyType; }

	/** Returns the current EnergyLevel this entity has. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentEnergyLevel() const { return EnergyLevel.Current; }

	/** Returns the highest possible EnergyLevel this entity can store. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentEnergyMax() const { return EnergyLevel.Max; }

	/** Returns the current EnergyLevel this entity has as a normalized value */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetEnergyLevelNormalized() const { return EnergyLevel.GetNormalizedValue(); }

	/** Returns whether or not the entity is an Energy-Container or an Energy-Source. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsEnergyContainer() const { return bContainer; }

	/** Returns whether or not the current EnergyLevel is equal to the maximum EnergyLevel. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsCharged() const { return bCharged; }

	/** Returns whether or not the entity can be charged with energy. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsChargeable() const { return bChargeable; }

	/** Returns whether or not the current EnergyLevel is <= 0 */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsDrained() const { return bDrained; }

	UFUNCTION(BlueprintCallable)
	/** Returns whether or not the entity can be drained for energy. */
	FORCEINLINE bool IsDrainable() const { return bDrainable; }

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	/** The Energy Type that this entity stores on spawn*/
	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	EEnergyType EnergyType;

	/** The EnergyLevel this entity has on spawn */
	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	float Energy;

	/** The maximum EnergyLevel this entity has on spawn */
	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
	float EnergyMax;

	/** Whether this entity will spawn as a container or as a source. By default this is set to false which means the entity is a source. */
	UPROPERTY(EditAnywhere, Category = "IMP Base|Energy")
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
