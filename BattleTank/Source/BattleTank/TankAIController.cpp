// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }
	UE_LOG(LogTemp, Warning, TEXT("%s AI Begin Play"), *(ControlledTank->GetName()));
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




