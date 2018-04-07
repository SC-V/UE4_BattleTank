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
	Locked,
	OutOfAmmo
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
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	// Interface for tanks aiming 
	void AimAt(FVector HitLocation);

	// Sets default values for this component's properties
	UTankAimingComponent();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;

private:
	virtual void BeginPlay() override; 
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	// Moves the barrel and turret on the tank
	void MoveBarrelTowards(FVector AimDirection);

	// Checks if the barrel moves
	bool IsBarrelMoving(FVector AimDirection);

	// Reloading state of the tank
	bool isReloaded = false;
	
	float LastFireTime = 0;

	FVector AimDirection;

protected:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	int RoundsLeft = 3;
};
