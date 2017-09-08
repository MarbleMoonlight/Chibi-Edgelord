// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

UCLASS()
class CHIBIEDGELORD_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

private:

	FVector FacingDirection = FVector(1.f, 0.f, 0.f);
	FVector CurrentDirectionInput;
	FVector LastDirectionInput;

	// Character Movement Functions
	void MoveForward(float InputValue);
	void MoveRight(float InputValue);

	// Character Facing Functions
	void LookForward(float InputValue);
	void LookRight(float InputValue);

	// Character Dashing Functions
	void Dash();
	void EndDash();
	void ExecuteDash();
	void UpdateMovementDirection();
	void DashDecelerate();
	void DashEndCD();

	// Variables for dashing
	FTimerHandle DashTimerHandle;
	FTimerHandle DashDecreaseTimerHandle;
	FTimerHandle DashCDHandle;

	bool bIsDashing = false;
	bool bDashOnCD = false;
	float DashDecreaseAmount = 0.f;

	void LookTowardsMouse();
	
};
