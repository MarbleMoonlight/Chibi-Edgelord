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
	virtual void Tick(float DeltaTime) override;

private:
	FVector FacingDirection;

	void MoveForward(float InputValue);
	void MoveRight(float InputValue);
	void LookForward(float InputValue);
	void LookRight(float InputValue);
	void LookTowardsMouse();
	
};
