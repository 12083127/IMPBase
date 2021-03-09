// IMP Project - Robert Lehmann 2020-2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMPPreviewCaptureBase.generated.h"

/* This actor provides functions and utilities to render a mesh preview to a Texture Render Target that can be controlled by user input. */
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
	/* Enable this to use Idle Rotation on the preview. */
	bool bUseIdleRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	/* Sets the rotation speed of the Idle Rotation feature. */
	float IdleRotationSpeed;

	UFUNCTION(BlueprintCallable)
	/* Gets the extends of the Preview Frame BoxComponent. Returns single float since it is uniform. */
	float GetPreviewFrameExtends() const;

	UFUNCTION(BlueprintCallable)
	/* Enable/Disable the render target to capture a live preview. Enable this when previewing and disable it when not to save performance.*/
	void SetCapturePreview(const bool bCapturePreview);

	UFUNCTION(BlueprintCallable)
	/* Rotate the Mesh Preview using the current mouse position */
	void RotateMeshPreview(FVector2D InMouseLocation);
	
	UFUNCTION(BlueprintCallable)
	/* Engage/Disengage in rotation performed by user input */
	void SetUserRotation(const bool bEnabled, const FVector2D MouseLocationStart);

	UFUNCTION(BlueprintCallable)
	/* Enable/Disable mesh preview rotation. */
	void SetIdleRotationActive(const bool bEnabled);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	/* Blueprint Event that defines the logic that needs to be performed to update the actors mesh. */
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
