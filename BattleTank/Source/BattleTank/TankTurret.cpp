// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f : Turret->Rotate() called at speed %f"), Time, RelativeSpeed)

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	//auto Rotation = FMath::Clamp<float>(RawNewRotation, MinElevationDegrees, MaxElevationDegrees);
	auto Rotation = RawNewRotation;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}
