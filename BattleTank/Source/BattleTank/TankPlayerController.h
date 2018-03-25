// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/Actor.h" //could be deleted
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	// Get pointer to the human controlled tank
	ATank * GetControlledTank() const;
	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector & HitLocation) const; 
	// Move the turret towards crosshair (position defined by GetSightRayHitLocation)
	void AimTowardsCrosshair();
	
public:
	virtual void Tick(float DeltaTime) override;

};
