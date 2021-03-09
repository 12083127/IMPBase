// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "IMPBase/IMPBase.h"
#include "IMPPlayer.generated.h"

UENUM()
enum class EPlayerState : uint8
{
	PT_EnergyMode,
	PT_ShootingMode
};

UCLASS()
class IMPBASE_API AIMPPlayer : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IMP Base", meta = (AllowPrivateAccess = "true"))
	class UIMPInventoryComponent* Inventory;

	class UAbilitySystemComponent* AbilitySystemComponent;
	class UIMPAttributeSetBase* AttributeSet;

public:
	// Sets default values for this character's properties
	AIMPPlayer();

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName InteractBinding;
	static const FName DrainBinding;
	static const FName ChargeBinding;
	static const FName SprintBinding;
	static const FName SwitchElementFireBinding;
	static const FName SwitchElementElectricBinding;
	static const FName SwitchElementWaterBinding;
	static const FName SwitchModeBinding;
	static const FName ImbuementSwitchBinding;
	static const FName TurnBinding;
	static const FName TurnRateBinding;
	static const FName LookUpBinding;
	static const FName LookUpRateBinding;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/*IMP Char Stats*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Attributes")
	TSubclassOf<class UGameplayEffect> StartupEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base|Abilities")
	TArray<TSubclassOf<class UIMPGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, Category = "IMP Base")
	class USkeletalMeshSocket* LethalProjectileSocket;

	UPROPERTY(EditAnywhere, Category = "IMP Base")
	class UBlueprint* LethalProjectile;

	TArray<float> PlayerEnergyLevels;
	TArray<float> PlayerEnergyLevelsMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IMP Base") // blueprint read only?
	EEnergyType ActiveElement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base")
	int32 LethalRoundsPerMinute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base")
	float LethalProjectileDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMP Base")
	float SprintingSpeed = 1500.f;

	float DrainingRate;
	float ChargingRate;

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(BlueprintReadOnly)
	FHitResult ShotActor;

	/* IMP Functions*/
	void ModifyPlayerEnergyLevels(EEnergyType EnergyType, float Amount, float DeltaTime);

	UFUNCTION(BlueprintCallable)
	float GetEnergyLevel_Normalized(EEnergyType EnergyType);

	UFUNCTION(BlueprintCallable)
	void SetPlayerEnergyLevels(EEnergyType EnergyType, float Amount);
	
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float amount);
	
	UFUNCTION(BlueprintCallable)
	void Heal(float amount);

	UFUNCTION(BlueprintCallable)
	void SetIsSprinting(const bool InValue);

	UFUNCTION(BlueprintCallable)
    FORCEINLINE float GetHealthNormalized() { return Health.GetNormalizedValue(); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE	float GetHealth() const { return Health.Current; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE	float GetHealthMax() const { return Health.Max; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetLethalAmmoNormalized() { return LethalAmmo.GetNormalizedValue(); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetLethalAmmoCount() const { return LethalAmmo.Current; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetLethalAmmoMax() const { return LethalAmmo.Max; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerState GetCurrentMode() const { return PlayerState; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool HasActiveElementEnergy() const { return (PlayerEnergyLevels[(int)ActiveElement] > 0.f); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool HasElementEnergy(EEnergyType type) const { return (PlayerEnergyLevels[(int)type] > 0.f); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool UsesImbuement() const { return bUseImbuedAmmo; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EEnergyType GetActiveElement() const { return ActiveElement; }

	UFUNCTION(BlueprintCallable)
	/* Returns whether the player is dead or not */
	FORCEINLINE bool IsDead() const { return bDead; }

	UFUNCTION(BlueprintCallable)
	/* Returns whether the player is sprinting or not */
	FORCEINLINE bool IsSprinting() const { return bIsSprinting; }

	/* Returns CameraBoom subobject */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/* Returns FollowCamera subobject */
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/* Returns FollowCamera subobject */
	FORCEINLINE class UIMPInventoryComponent* GetInventoryComponent() const { return Inventory; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void InitializeAbilities();

	UFUNCTION(BlueprintCallable)
	float GetStamina() const;

	UFUNCTION(BlueprintCallable)
	float GetStaminaMax() const;

	UFUNCTION(BlueprintCallable)
	float GetStaminaNormalized() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxSpeed() const;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	virtual void BeginPlay() override;

	/* IMP Functions*/
	void UseInteractable();
	void StopInteractable();
	void StartSprinting();
	void StopSprinting();
	void SwitchToFire();
	void SwitchToElectric();
	void SwitchToWater();
	void SwitchMode();

	UFUNCTION(BlueprintNativeEvent)
	void OnDrainEnergy(float DeltaTime);
	virtual void OnDrainEnergy_Implementation(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	void OnChargeEnergy(float DeltaTime);
	virtual void OnChargeEnergy_Implementation(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	void OnShootLethal();
	virtual void OnShootLethal_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void OnShootEnergy(float DeltaTime);
	virtual void OnShootEnergy_Implementation(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// vars
	uint8 ActiveMode;
	EPlayerState PlayerState;
	FAttributeFloat Health;
	FAttributeInt LethalAmmo;

	FTimerHandle FireRateHandle;
	
	UPROPERTY()
	class AIMPInteractableBase* CurrentInteractable;
	
	UPROPERTY()
	class AIMPInteractableBase* LastKnownInteractable;
	
	UPROPERTY()
	class AIMPNPCCharacterBase* CurrentNPC;
	
	UPROPERTY()
	class AIMPNPCCharacterBase* LastKnownNPC;

	UPROPERTY()
	class UIMPEnergyComponent* EnergyComponent;

	bool bDead;

	bool bDraining;
	bool bCharging;
	bool bIsSprinting;
	bool bUseImbuedAmmo;
	bool bInCharMenu;

	float InitialWalkSpeed; // const?


	// functions
	void KillPlayer();
	void StartDraining();
	void StopDraining();
	void StartCharging();
	void StopCharging();
	void SwitchImbuement();
	void ToggleCharMenu();
	void ShootLethalProjetile(float Distance);
	AActor* GetFocusedActor(float WithinDistance);
	void UseShootingPlayerMovement(bool InValue);
};
