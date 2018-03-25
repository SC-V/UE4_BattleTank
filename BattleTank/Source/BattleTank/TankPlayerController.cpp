// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }
	UE_LOG(LogTemp, Warning, TEXT("%s Begin Play"), *(ControlledTank->GetName()));
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
