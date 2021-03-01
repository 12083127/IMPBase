// IMP Project - Robert Lehmann 2020-2021


#include "IMPPlayer.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//#include "GameplayEffect.h"

#include "IMPBase/Actor/IMPEnergyActor.h"
#include "IMPBase/Actor/IMPInteractableBase.h"
#include "IMPBase/AI/IMPNPCCharacterBase.h"
#include "IMPBase/AI/IMPNPCCharacterAIBase.h"

#include "IMPBase/Components/IMPEnergyComponent.h"
#include "IMPBase/Components/IMPInventoryComponent.h"

#include "IMPBase/Utility/IMPAttributeSetBase.h"
#include "IMPBase/Utility/IMPInteractInterface.h"
#include "IMPBase/Utility/IMPGameplayAbility.h"

#include "DrawDebugHelpers.h"

const FName AIMPPlayer::MoveForwardBinding("MoveForward");
const FName AIMPPlayer::MoveRightBinding("MoveRight");
const FName AIMPPlayer::InteractBinding("Use");
const FName AIMPPlayer::DrainBinding("Drain");
const FName AIMPPlayer::ChargeBinding("Charge");
const FName AIMPPlayer::SprintBinding("AI_Sprint");
const FName AIMPPlayer::SwitchElementFireBinding("SwitchElementFire");
const FName AIMPPlayer::SwitchElementElectricBinding("SwitchElementElectric");
const FName AIMPPlayer::SwitchElementWaterBinding("SwitchElementWater");
const FName AIMPPlayer::SwitchModeBinding("SwitchMode");
const FName AIMPPlayer::ImbuementSwitchBinding("ImbueSwitch");
const FName AIMPPlayer::TurnBinding("Turn");
const FName AIMPPlayer::TurnRateBinding("TurnRate");
const FName AIMPPlayer::LookUpBinding("LookUp");
const FName AIMPPlayer::LookUpRateBinding("LookUpRate");
const FName AIMPPlayer::CharMenuBinding("CharMenu");

// Sets default values
AIMPPlayer::AIMPPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(false);

	AttributeSet = CreateDefaultSubobject<UIMPAttributeSetBase>(TEXT("AttributeSet"));

	Inventory = CreateDefaultSubobject<UIMPInventoryComponent>(TEXT("InventoryComponent"));

	/*Init IMP Player Stats*/
	CurrentInteractable = nullptr;
	LastKnownInteractable = nullptr;
	LethalProjectile = nullptr;
	LethalProjectileSocket = nullptr;
	CurrentNPC = nullptr;
	LastKnownNPC = nullptr;
	EnergyComponent = nullptr;

	InitialWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	ActiveElement = EEnergyType::ET_Fire;
	ActiveMode = (uint8)EPlayerState::PT_EnergyMode;

	PlayerEnergyLevels.Init(0, 4);
	PlayerEnergyLevelsMax.Init(100, 4);

	LethalAmmo.Max = 100;
	LethalAmmo.Current = LethalAmmo.Max;
	LethalRoundsPerMinute = 200;
	LethalProjectileDamage = 100.f;

	Health.Max = 100.f;
	Health.Current = Health.Max;

	DrainingRate = 100.f;
	ChargingRate = 25.f;

	bDead = false;
	bIsSprinting = false;
	bUseImbuedAmmo = false;
	bInCharMenu = false;
}

void AIMPPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		InitializeAttributes();
		InitializeAbilities();
	}
}

void AIMPPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// replace this later...
	float GeneralScanDistance = 750.f;

	LastKnownInteractable = CurrentInteractable;
	LastKnownNPC = CurrentNPC;

	//check for interactable actors within player focus
	FocusedActor = GetFocusedActor(GeneralScanDistance);

#pragma region Focus-Handling-Logic
	if (FocusedActor)
	{
		AIMPInteractableBase* Interactable = Cast<AIMPInteractableBase>(FocusedActor);
		if (Interactable)
		{
			Interactable->SetInFocus(true);
			CurrentInteractable = Interactable;
		}
		else
		{
			CurrentInteractable = nullptr;
		}

		EnergyComponent = FocusedActor->FindComponentByClass<UIMPEnergyComponent>();
		AIMPNPCCharacterBase* NPC = Cast<AIMPNPCCharacterBase>(FocusedActor);
		if (NPC && EnergyComponent)
		{
			if (EnergyComponent->IsDrainable())
			{
				NPC->SetInFocus(true);
			}
			else
			{
				NPC->SetInFocus(false);
			}

			CurrentNPC = NPC;
		}
		else
		{
			CurrentNPC = nullptr;
		}
	}
	else
	{
		CurrentInteractable = nullptr;
		CurrentNPC = nullptr;
		EnergyComponent = nullptr;
	}

	// clear focus if we know the last interactable/npc and it is not the current interactable/npc
	if (LastKnownInteractable && LastKnownInteractable != CurrentInteractable)
	{
		LastKnownInteractable->ResetInteractionTimer();
		LastKnownInteractable->SetInFocus(false);
	}
	if (LastKnownNPC && LastKnownNPC != CurrentNPC)
	{
		LastKnownNPC->SetInFocus(false);
	}
#pragma endregion

#pragma region State-Machine

	if (bDraining)
	{
		if (EnergyComponent)
		{
			EEnergyType ComponentEnergyType = EnergyComponent->GetEnergyType();
			bool bDrainable = EnergyComponent->IsDrainable();
			bool bPlayerCanStoreEnergy = PlayerEnergyLevels[(int)(ComponentEnergyType)] < PlayerEnergyLevelsMax[(int)(ComponentEnergyType)];

			if (bDrainable && bPlayerCanStoreEnergy)
			{
				OnDrainEnergy(DeltaTime);
			}
		}
	}

	switch (PlayerState)
	{
		case EPlayerState::PT_EnergyMode:
		{
			if (bCharging && HasActiveElementEnergy())
			{
				if (EnergyComponent)
				{
					EEnergyType ComponentEnergyType = EnergyComponent->GetEnergyType();
					bool bSameElement = ComponentEnergyType == ActiveElement;
					bool bChargeable = EnergyComponent->IsChargeable();

					if (bSameElement && bChargeable)
					{
						OnChargeEnergy(DeltaTime);
					}
				}
				else
				{
					OnShootEnergy(DeltaTime);
				}
			}
			break;
		}

		case EPlayerState::PT_ShootingMode:
		{
			if (bCharging)
			{
				if (GetWorldTimerManager().IsTimerActive(FireRateHandle) && LethalAmmo.Current <= 0)
				{
					GetWorldTimerManager().ClearTimer(FireRateHandle);
				}
			}
			break;
		}

		default: break;
	}
#pragma endregion

	// health regen hack
	Heal(5.f * DeltaTime);
}

// Called to bind functionality to input
void AIMPPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AIMPPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIMPPlayer::MoveRight);

	PlayerInputComponent->BindAction(InteractBinding, IE_Pressed, this, &AIMPPlayer::UseInteractable).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction(InteractBinding, IE_Released, this, &AIMPPlayer::StopInteractable).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction(DrainBinding, IE_Pressed, this, &AIMPPlayer::StartDraining);
	PlayerInputComponent->BindAction(DrainBinding, IE_Released, this, &AIMPPlayer::StopDraining);
	PlayerInputComponent->BindAction(ChargeBinding, IE_Pressed, this, &AIMPPlayer::StartCharging);
	PlayerInputComponent->BindAction(ChargeBinding, IE_Released, this, &AIMPPlayer::StopCharging);
	PlayerInputComponent->BindAction(SprintBinding, IE_Pressed, this, &AIMPPlayer::StartSprinting);
	PlayerInputComponent->BindAction(SprintBinding, IE_Released, this, &AIMPPlayer::StopSprinting);
	PlayerInputComponent->BindAction(SwitchElementFireBinding, IE_Pressed, this, &AIMPPlayer::SwitchToFire);
	PlayerInputComponent->BindAction(SwitchElementElectricBinding, IE_Pressed, this, &AIMPPlayer::SwitchToElectric);
	PlayerInputComponent->BindAction(SwitchElementWaterBinding, IE_Pressed, this, &AIMPPlayer::SwitchToWater);
	PlayerInputComponent->BindAction(SwitchModeBinding, IE_Pressed, this, &AIMPPlayer::SwitchMode);
	PlayerInputComponent->BindAction(ImbuementSwitchBinding, IE_Pressed, this, &AIMPPlayer::SwitchImbuement);
	PlayerInputComponent->BindAction(CharMenuBinding, IE_Pressed, this, &AIMPPlayer::ToggleCharMenu).bExecuteWhenPaused = true;

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AIMPPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AIMPPlayer::LookUpAtRate);

	// Initialize GAS Input Binds
	if (AbilitySystemComponent && InputComponent)
	{
		int32 ConfirmActionID = static_cast<int32>(EIMPAbilityInputID::AI_Confirm);
		int32 CancelActionID = static_cast<int32>(EIMPAbilityInputID::AI_Cancel);

		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EIMPAbilityInputID", ConfirmActionID, CancelActionID);
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

UAbilitySystemComponent* AIMPPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AIMPPlayer::InitializeAttributes()
{
	if (DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}

		NewHandle = AbilitySystemComponent->MakeOutgoingSpec(StartupEffects, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}

void AIMPPlayer::InitializeAbilities()
{
	for (TSubclassOf<UIMPGameplayAbility>& StartupAbility : DefaultAbilities)
	{
		int32 InputID = static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID);

		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, InputID, this));
	}
}

float AIMPPlayer::GetStamina() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetStamina();
	}

	return 0.f;
}

float AIMPPlayer::GetStaminaMax() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetStaminaMax();
	}

	return 0.f;
}

float AIMPPlayer::GetStaminaNormalized() const
{
	float StaminaMax = GetStaminaMax();
	float Stamina = GetStamina();

	if (StaminaMax != 0.f)
	{
		return Stamina / StaminaMax;
	}

	return 0.f;
}

float AIMPPlayer::GetMaxSpeed() const
{
	if (bDead)
	{
		return 0.f;
	}

	if (bIsSprinting)
	{
		return SprintingSpeed;
	}

	return InitialWalkSpeed;
}

void AIMPPlayer::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AIMPPlayer::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AIMPPlayer::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AIMPPlayer::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AIMPPlayer::UseInteractable()
{
	if (CurrentInteractable)
	{
		IIMPInteractInterface* Interface = Cast<IIMPInteractInterface>(CurrentInteractable);
		if (Interface)
		{
			Interface->Execute_OnInteract(CurrentInteractable);
		}
	}
}

void AIMPPlayer::StopInteractable()
{
	if (CurrentInteractable)
	{
		IIMPInteractInterface* Interface = Cast<IIMPInteractInterface>(CurrentInteractable);
		if (Interface)
		{
			Interface->Execute_OnInteractStop(CurrentInteractable);
		}
	}
}

void AIMPPlayer::StartSprinting()
{
	if (!bDead)
	{
		bIsSprinting = true;
	}
}

void AIMPPlayer::StopSprinting()
{
	bIsSprinting = false;
}

void AIMPPlayer::SwitchToFire()
{
	if (!bDead)
	{
		ActiveElement = EEnergyType::ET_Fire;
	}
}

void AIMPPlayer::SwitchToElectric()
{
	if (!bDead)
	{
		ActiveElement = EEnergyType::ET_Electric;
	}
}

void AIMPPlayer::SwitchToWater()
{
	if (!bDead)
	{
		ActiveElement = EEnergyType::ET_Water;
	}
}

void AIMPPlayer::SwitchImbuement()
{
	bUseImbuedAmmo = !bUseImbuedAmmo;
}

void AIMPPlayer::ToggleCharMenu()
{
	bInCharMenu = !bInCharMenu;
}

void AIMPPlayer::SwitchMode()
{
	if (!bDead)
	{
		PlayerState = (EPlayerState)(++ActiveMode % 2);
	}
}

void AIMPPlayer::StartDraining()
{
	if (!bDead)
	{
		bDraining = true;
	}
}

void AIMPPlayer::StopDraining()
{
	bDraining = false;

	UseShootingPlayerMovement(false);
}

void AIMPPlayer::StartCharging()
{
	if (!bDead)
	{
		bCharging = true;

		if (PlayerState == EPlayerState::PT_ShootingMode)
		{
			bool bHasAmmo = LethalAmmo.Current > 0;
			bool bValidProjectile = LethalProjectile != nullptr;
			bool bValidProjectileSocket = LethalProjectileSocket != nullptr;

			if (bHasAmmo) // && bValidProjectile && bValidProjectileSocket)
			{
				float rps = (float)(LethalRoundsPerMinute / 60);
				GetWorldTimerManager().SetTimer(FireRateHandle, this, &AIMPPlayer::OnShootLethal, 1.f / rps, true, 0.f);
			}
		}
	}
}

void AIMPPlayer::StopCharging()
{
	bCharging = false;

	UseShootingPlayerMovement(false);

	if (GetWorldTimerManager().IsTimerActive(FireRateHandle))
	{
		GetWorldTimerManager().ClearTimer(FireRateHandle);
	}
}

void AIMPPlayer::ModifyPlayerEnergyLevels(EEnergyType EnergyType, float Amount, float DeltaTime)
{
	PlayerEnergyLevels[(int)EnergyType] += Amount * DeltaTime;
	PlayerEnergyLevels[(int)EnergyType] = FMath::Clamp(PlayerEnergyLevels[(int)EnergyType], 0.f, PlayerEnergyLevelsMax[(int)EnergyType]);
}

float AIMPPlayer::GetEnergyLevel_Normalized(EEnergyType EnergyType)
{
	if (PlayerEnergyLevelsMax[(int)EnergyType] != 0.f)
	{
		return PlayerEnergyLevels[(int)EnergyType] / PlayerEnergyLevelsMax[(int)EnergyType];
	}

	return 0.f;
}

void AIMPPlayer::SetPlayerEnergyLevels(EEnergyType EnergyType, float Amount)
{
	PlayerEnergyLevels[(int)EnergyType] += Amount;
	PlayerEnergyLevels[(int)EnergyType] = FMath::Clamp(PlayerEnergyLevels[(int)EnergyType], 0.f, PlayerEnergyLevelsMax[(int)EnergyType]);
}

void AIMPPlayer::ReceiveDamage(float amount)
{
	if (!bDead)
	{
		Health.Modify(-amount);

		if (Health.Current <= 0.f)
		{
			KillPlayer();
		}
	}
}

void AIMPPlayer::Heal(float amount)
{
	if (!bDead)
	{
		Health.Modify(amount);
	}
}

void AIMPPlayer::SetIsSprinting(const bool InValue)
{
	bIsSprinting = InValue;
}

void AIMPPlayer::OnDrainEnergy_Implementation(float DeltaTime)
{
	UseShootingPlayerMovement(true);
	EnergyComponent->ModifyCurrentEnergyLevel(-(DrainingRate * DeltaTime));
	ModifyPlayerEnergyLevels(EnergyComponent->GetEnergyType(), DrainingRate, DeltaTime);
}

void AIMPPlayer::OnChargeEnergy_Implementation(float DeltaTime)
{
	UseShootingPlayerMovement(true);
	ModifyPlayerEnergyLevels(EnergyComponent->GetEnergyType(), -ChargingRate, DeltaTime);
	EnergyComponent->ModifyCurrentEnergyLevel(ChargingRate * DeltaTime);
}

void AIMPPlayer::OnShootLethal_Implementation()
{
	UseShootingPlayerMovement(true);
	ShootLethalProjetile(5000.f);
}

void AIMPPlayer::OnShootEnergy_Implementation(float DeltaTime)
{
	UseShootingPlayerMovement(true);
	ModifyPlayerEnergyLevels(ActiveElement, -ChargingRate * 0.5f, DeltaTime);
}

void AIMPPlayer::KillPlayer()
{
	bDead = true;
	CameraBoom->TargetArmLength = 1000.f;

	// TODO disable Collisions
	GetController()->SetIgnoreMoveInput(true);
	GetMesh()->SetSimulatePhysics(true);

	UCapsuleComponent* collComp = GetCapsuleComponent();

	if (collComp)
	{
		collComp->SetCollisionProfileName("NoCollision", false);
	}
}

void AIMPPlayer::ShootLethalProjetile(float Distance)
{
	LethalAmmo.Modify(-1);

	if (bUseImbuedAmmo && HasActiveElementEnergy())
	{
		ModifyPlayerEnergyLevels(ActiveElement, -ChargingRate * 0.5f, GetWorld()->GetDeltaSeconds());
	}

	FVector traceStart = FollowCamera->GetComponentLocation();
	FVector forwardVector = FollowCamera->GetForwardVector();
	FVector traceEnd = traceStart + forwardVector * Distance;

	FCollisionQueryParams queryParams;

	// remove player actor from trace result
	queryParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Green, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(ShotActor, traceStart, traceEnd, ECC_Shootable, queryParams))
	{
		AIMPNPCCharacterBase* shotNPC = Cast<AIMPNPCCharacterBase>(ShotActor.GetActor());

		if (shotNPC)
		{
			FVector hitImpulse = ShotActor.ImpactPoint - ShotActor.TraceStart;

			shotNPC->DamageNPC(LethalProjectileDamage, hitImpulse.GetSafeNormal());
		}
	}

	//FRotator controllerRot = Controller->GetControlRotation();
	//FRotator actorRot = GetActorRotation();
	//FRotator newRot = UKismetMathLibrary::NormalizedDeltaRotator(controllerRot, actorRot);
	//Controller->SetControlRotation(newRot);
	//UKismetMathLibrary::RInterpTo();
}

AActor* AIMPPlayer::GetFocusedActor(float WithinDistance)
{
	FHitResult hitResult;

	FVector traceStart = FollowCamera->GetComponentLocation();
	FVector forwardVector = FollowCamera->GetForwardVector();
	FVector traceEnd = traceStart + forwardVector * WithinDistance;

	FCollisionQueryParams queryParams;

	// remove player actor from trace result
	queryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, traceStart, traceEnd, ECC_Focusable, queryParams))
	{
		//DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Green, false, 1, 0, 1);
		return hitResult.GetActor();
	}

	return nullptr;
}

void AIMPPlayer::UseShootingPlayerMovement(bool InValue)
{
	GetCharacterMovement()->MaxWalkSpeed = (100.f * InValue) + (InitialWalkSpeed * !InValue);
	bUseControllerRotationYaw = InValue;

	//if (InValue)
	//{
	//	GetCharacterMovement()->MaxWalkSpeed = 100.f;
	//	bUseControllerRotationYaw = true;
	//}
	//else
	//{
	//	GetCharacterMovement()->MaxWalkSpeed = InitialWalkSpeed;
	//	bUseControllerRotationYaw = false;
	//}
}
