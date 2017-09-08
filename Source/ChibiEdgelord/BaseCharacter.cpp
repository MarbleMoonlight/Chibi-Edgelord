// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::CalculateDead()
{
	if (this->Health <= 0)
		this->bIsDead = true;
	else
		this->bIsDead = false;
}

void ABaseCharacter::CalculateHealth(float delta)
{
	this->Health += delta;
	CalculateDead();
}

/*
// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

