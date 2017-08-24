// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class CHIBIEDGELORD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	//Amount of health character currently has
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	float Health = 100;

	//Bool claiming if character is dead or not
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Base Character")
	bool bIsDead = false;

	//Calculates if character is dead
	virtual void CalculateDead();

	//Calculates current health
	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void CalculateHealth(float delta);

public:
	// Sets default values for this character's properties
	ABaseCharacter();

public:	
	

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
