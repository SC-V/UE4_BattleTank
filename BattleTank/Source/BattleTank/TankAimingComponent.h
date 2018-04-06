// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class AProjectile; // Forvard declaration
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
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Fire();

	// Interface for tanks aiming 
	void AimAt(FVector HitLocation);

	// Sets default values for this component's properties
	UTankAimingComponent();

private:
	// Moves the barrel and turret on the tank
	void MoveBarrelTowards(FVector AimDirection);

	// Reloading state of the tank
	bool isReloaded = false;
	
	float LastFireTime = 0;
protected:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

};
