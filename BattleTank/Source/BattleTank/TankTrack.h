// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float TrackMaxDrivingForce = 40000000; // Assume 40 tonne tank and 1g acceleration
	
private:
	UTankTrack();
	virtual void BeginPlay() override;

	// Apply sideways force to prevent tank from sliding on the surface
	void ApplySidewaysForce();
	// Apply force to tracks to rotate and move forward/backward
	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

	float CurrentThrottle = 0;
};
