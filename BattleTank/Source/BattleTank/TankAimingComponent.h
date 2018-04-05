// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UTankBarrel; // Forvard declaration
class UTankTurret; // Forvard declaration

UENUM(BlueprintType)
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);
	
	// Interface for tanks aiming 
	void AimAt(FVector HitLocation, float LaunchSpeed);

	// Sets default values for this component's properties
	UTankAimingComponent();


private:
	void MoveBarrelTowards(FVector AimDirection);
	// void MoveTurretTowards(FVector AimDirection);

protected:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
};
