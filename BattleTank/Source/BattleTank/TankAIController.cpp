// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!ControlledTank) { return; }
	if (!PlayerTank) { return; }
	UE_LOG(LogTemp, Warning, TEXT("%s AI Begin Play"), *(ControlledTank->GetName()));
	UE_LOG(LogTemp, Warning, TEXT("AI has found a human player: %s"), *(PlayerTank->GetName()));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) 
	{
		// TODO Move towards the player
		
		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetTargetLocation());

		// TODO Fire if ready
	}
}

// Get AI controlled pawn
ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Get human controlled pawn
ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


