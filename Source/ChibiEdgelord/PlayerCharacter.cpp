// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookForward", this, &APlayerCharacter::LookForward);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->FacingDirection.IsZero())
		this->SetActorRotation(FacingDirection.Rotation());

}

void APlayerCharacter::MoveForward(float InputValue)
{
	if (this->Controller != nullptr && InputValue != 0.0f)
		AddMovementInput(FVector(1.f,0.f,0.f),InputValue*100.f);
}

void APlayerCharacter::MoveRight(float InputValue)
{
	if (this->Controller != nullptr && InputValue != 0.0f)
		AddMovementInput(FVector(0.f,1.f,0.f), InputValue*100.f);
}

void APlayerCharacter::LookForward(float InputValue)
{
	if (this->Controller != nullptr && InputValue != 0.0f)
		this->FacingDirection.X = InputValue*-1.f;
}

void APlayerCharacter::LookRight(float InputValue)
{
	if (Controller != nullptr && InputValue != 0.0f)
		this->FacingDirection.Y = InputValue;
}

