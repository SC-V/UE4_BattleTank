// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Ticking!"))
	if (!ensure(Barrel)) { return; }

	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds) 
	{ 
		FiringState = EFiringState::Reloading; 
	}
	else if (IsBarrelMoving(AimDirection))
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
	isReloaded = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)	{
				AimDirection = OutLaunchVelocity.GetSafeNormal();
				MoveBarrelTowards(AimDirection);
				IsBarrelMoving(AimDirection);
			}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// Work-out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) > 180.F)
	{
		DeltaRotator.Yaw *= -1.F;
	}

	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving(FVector AimDirection)
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	return !(BarrelForwardVector.FVector::Equals(AimDirection, 0.001
	));
}

void UTankAimingComponent::Fire()
{
	// Debug line: UE_LOG(LogTemp, Error, TEXT("Fire function is called, barrel is found"))
	
	// Spawn a projectile
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		FiringState = EFiringState::Reloading;
		RoundsLeft--;
	}
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}