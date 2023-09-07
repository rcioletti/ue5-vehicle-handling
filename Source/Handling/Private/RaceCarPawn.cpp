// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceCarPawn.h"
#include "Engine/World.h"
#include "WheeledVehiclePawn.h"
#include "Kismet/GameplayStatics.h"

ARaceCarPawn::ARaceCarPawn() {

	ChaosWheeledVehicleMovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(this->GetVehicleMovement());
	
	WheelAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("WheelAudio"));
	WheelAudioComponent->SetupAttachment(GetMesh());

	EngineAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineAudio"));
	EngineAudioComponent->SetupAttachment(GetMesh());
	
	ExhaustAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ExhaustAudio"));
	ExhaustAudioComponent->SetupAttachment(GetMesh());
}

void ARaceCarPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeCounter = DeltaSeconds + TimeCounter;

	OnTireSkid();
	PlayEngineSound();
	OnGearChange();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Name: %s"), *Name));
}

void ARaceCarPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ARaceCarPawn::OnTireSkid()
{
	if (WheelAudioComponent->Sound) {

		TArray<UChaosVehicleWheel*> WheelList = ChaosWheeledVehicleMovementComponent->Wheels;
		IsSkidding = false;

		for (int32 i = 0; i < ChaosWheeledVehicleMovementComponent->GetNumWheels() - 1; i++) {

			if (!IsSkidding) {
				
				IsSkidding = ChaosWheeledVehicleMovementComponent->GetWheelState(i).bIsSkidding;
			}

			if (ChaosWheeledVehicleMovementComponent->GetWheelState(i).bIsSkidding) {
				
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
					WheelSmokeParticle, 
					ChaosWheeledVehicleMovementComponent->GetWheelState(i).ContactPoint,
					FRotator(0.0f, 90.0f, 0.0f), 
					FVector(0.4f, 0.4f, 0.4f),
					true,
					EPSCPoolMethod::AutoRelease,
					true);
			}
		}

		//Play Tire Skid Sound
		if (IsSkidding) {
			CurrentWheelSkidVolume = FMath::FInterpTo(CurrentWheelSkidVolume, 0.1, GetWorld()->GetDeltaSeconds(), 8.0f);
			WheelAudioComponent->SetVolumeMultiplier(CurrentWheelSkidVolume);
		}
		else {
			CurrentWheelSkidVolume = FMath::FInterpTo(CurrentWheelSkidVolume, 0.0f, GetWorld()->GetDeltaSeconds(), 8.0f);
			WheelAudioComponent->SetVolumeMultiplier(CurrentWheelSkidVolume);
		}
	}
}

void ARaceCarPawn::PlayEngineSound()
{
	if (EngineAudioComponent->Sound) {
		EngineAudioComponent->SetFloatParameter("RPM", ChaosWheeledVehicleMovementComponent->GetEngineRotationSpeed());
	}
}

void ARaceCarPawn::OnGearChange()
{
	if (ExhaustAudioComponent->Sound) {
	
		//Gear Change Up
		if (ChaosWheeledVehicleMovementComponent->GetCurrentGear() > CurrentGear) {

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Name: %s"), *ExhaustAudioComponent->GetComponentLocation().ToString()));
		}

		//Gear change Down
		if (ChaosWheeledVehicleMovementComponent->GetCurrentGear() < CurrentGear) {
			
			//Play Exhaust Pops
			ExhaustAudioComponent->Play();

			UGameplayStatics::SpawnEmitterAttached(ExhaustPopParticle, ExhaustAudioComponent, NAME_None, FVector(0.0f, 0.0f, 0.0f), FRotator(0.f, 0.f, 0.f), FVector(0.2f, 0.2f, 0.2f));
		}

		if (ChaosWheeledVehicleMovementComponent->GetForwardSpeedMPH() != 0) {
			ChaosWheeledVehicleMovementComponent->bReverseAsBrake = false;
		}
		else {
			ChaosWheeledVehicleMovementComponent->bReverseAsBrake = true;
		}

		CurrentGear = ChaosWheeledVehicleMovementComponent->GetCurrentGear();
	}
}

void ARaceCarPawn::ClearTimer()
{
	LapTimes.Add(TimeCounter);
	TimeCounter = 0.0f;
}

float ARaceCarPawn::GetCurrentBestTime()
{
	if (FMath::Min<float>(LapTimes) != NULL)
	{
		return FMath::Min<float>(LapTimes);
	}
	else {
		return 0.0f;
	}
}
