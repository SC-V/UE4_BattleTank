// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankTrack.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	//
}


void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!ensure(Barrel)) { return; }
	// Debug line: UE_LOG(LogTemp, Error, TEXT("Fire function is called, barrel is found"))
	// Spawn a projectile
	if (Barrel && isReloaded && ProjectileBlueprint)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

