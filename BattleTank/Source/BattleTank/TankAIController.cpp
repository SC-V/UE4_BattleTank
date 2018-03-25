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

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


