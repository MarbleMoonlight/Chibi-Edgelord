// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


const float INPUT_DEAD_ZONE = .1f;

const float DEFAULT_SPEED = 500.f;

//DASHING CONSTANTS
const float DASH_TIME = .20f;
const float BACK_DASH_TIME = .15f;
const float DASH_CD_TIME = .1f;
const float DASH_SPEED = 5000.f;
const float DECELERATE_MULTI = 500.f;
const float DECELERATE_INCREMENT_TIME = .02f;
const float MAX_ACCEL = 20000.f;


void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookForward", this, &APlayerCharacter::LookForward);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement()->MaxWalkSpeed = DEFAULT_SPEED;
	GetCharacterMovement()->MaxAcceleration = MAX_ACCEL;
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(DashTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(DashDecreaseTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(DashCDHandle);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovementDirection();

	if (!this->FacingDirection.IsZero())
		this->SetActorRotation(FacingDirection.Rotation());

	if (this->bIsDashing)
		this->ExecuteDash();
}

void APlayerCharacter::MoveForward(float InputValue)
{
	if (FMath::Abs(InputValue) < INPUT_DEAD_ZONE)
		this->CurrentDirectionInput.X = 0.f;
	else
		this->CurrentDirectionInput.X = InputValue;

	if (this->Controller != nullptr && InputValue != 0.0f && !bIsDashing)
		AddMovementInput(FVector(1.f,0.f,0.f),InputValue);

}

void APlayerCharacter::MoveRight(float InputValue)
{
	if (FMath::Abs(InputValue) < INPUT_DEAD_ZONE)
		this->CurrentDirectionInput.Y = 0.f;
	else
		this->CurrentDirectionInput.Y = InputValue;

	if (this->Controller != nullptr && InputValue != 0.0f && !bIsDashing)
		AddMovementInput(FVector(0.f,1.f,0.f), InputValue);
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

void APlayerCharacter::Dash()
{
	if (!bIsDashing && !bDashOnCD)
	{
		this->bIsDashing = true;
		this->bDashOnCD = true;

		float dashTime = DASH_TIME;

		//If the player is not pressing a direction, they'll backdash
		if (FMath::Abs(CurrentDirectionInput.X) < INPUT_DEAD_ZONE && FMath::Abs(CurrentDirectionInput.Y) < INPUT_DEAD_ZONE)
		{
			LastDirectionInput = FVector(FacingDirection.X * -1.f, FacingDirection.Y *-1.f, 0.f);
			dashTime = BACK_DASH_TIME;
		}

		GetCharacterMovement()->MaxWalkSpeed = DASH_SPEED;
		GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &APlayerCharacter::EndDash, dashTime, false);
		GetWorld()->GetTimerManager().SetTimer(DashDecreaseTimerHandle, this, &APlayerCharacter::DashDecelerate, DECELERATE_INCREMENT_TIME, true);
	}
}

void APlayerCharacter::EndDash()
{
	LastDirectionInput = FVector(0.f, 0.f, 0.f);
	DashDecreaseAmount = 0.f;
	GetCharacterMovement()->MaxWalkSpeed = DEFAULT_SPEED;
	GetWorld()->GetTimerManager().ClearTimer(DashDecreaseTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(DashCDHandle, this, &APlayerCharacter::DashEndCD, DASH_CD_TIME, false);
	this->bIsDashing = false;
}

void APlayerCharacter::ExecuteDash()
{
	if (!LastDirectionInput.IsZero())
	{
		AddMovementInput(LastDirectionInput, DASH_SPEED-(DECELERATE_MULTI * DashDecreaseAmount));
	}
}

void APlayerCharacter::UpdateMovementDirection()
{
	if (!bIsDashing)
		return;

	if ((FMath::Abs(CurrentDirectionInput.X) > INPUT_DEAD_ZONE || FMath::Abs(CurrentDirectionInput.Y) > INPUT_DEAD_ZONE))
		LastDirectionInput = CurrentDirectionInput;

	float compareFloatX = LastDirectionInput.X;
	float compareFloatY = LastDirectionInput.Y;

	compareFloatX = FMath::Abs(compareFloatX);
	compareFloatY = FMath::Abs(compareFloatY);

	LastDirectionInput.X = (LastDirectionInput.X >= 0.f) ? compareFloatX : compareFloatX *-1.f;
	LastDirectionInput.Y = (LastDirectionInput.Y >= 0.f) ? compareFloatY : compareFloatY *-1.f;
}

void APlayerCharacter::DashDecelerate()
{
	this->DashDecreaseAmount += 1.f;
}

void APlayerCharacter::DashEndCD()
{
	this->bDashOnCD = false;
}