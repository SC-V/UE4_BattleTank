// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	
	// How close the AI tank can get to the player
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 10000;

public:
	virtual void Tick(float DeltaTime) override;

private:
	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();
};
