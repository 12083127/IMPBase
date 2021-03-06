// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMPPreviewCaptureBase.generated.h"

UCLASS(Abstract)
class IMPBASE_API AIMPPreviewCaptureBase : public AActor
{
	GENERATED_BODY()

	class UBoxComponent* PreviewFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RotationPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* CaptureComponent;

public:	
	// Sets default values for this actor's properties
	AIMPPreviewCaptureBase();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUseIdleRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float IdleRotationSpeed;

	UFUNCTION(BlueprintCallable)
	float GetPreviewFrameExtends() const;

	UFUNCTION(BlueprintCallable)
	void SetCapturePreview(const bool bCapturePreview);

	UFUNCTION(BlueprintCallable)
	void RotateMeshPreview(FVector2D InMouseLocation);
	
	UFUNCTION(BlueprintCallable)
	void SetUserRotation(const bool bEnabled, const FVector2D MouseLocationStart);

	UFUNCTION(BlueprintCallable)
	void SetIdleRotationActive(const bool bEnabled);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	/** A placeholder Interface event that defines what happens when interacting with the Interactable. */
	void UpdatePreviewMesh(class UIMPInventoryItemBase* ActiveItem);
	virtual void UpdatePreviewMesh_Implementation(class UIMPInventoryItemBase* ActiveItem);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool bUserRotation;
	bool bIdleRotationActive;

	FVector2D MouseLocation;
};
