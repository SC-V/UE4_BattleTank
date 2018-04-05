// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class UTankAimingComponent; // Forward declarations
class UTankTrack; class UTankBarrel;
class UTankTurret; class AProjectile; 
UCLASS()
class BATTLETANK_API ATank : public APawn //inheritance: ATank is a subtype of APawn which is a subtype of AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * TankAimingComponent = nullptr;

private:
	void BeginPlay() override;
	
	// TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; 

	UTankBarrel * Barrel = nullptr; // TODO Remove
	
	float LastFireTime = 0;
};
