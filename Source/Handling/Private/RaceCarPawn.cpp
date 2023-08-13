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
		}

		//Play Tire Skid Sound
		IsSkidding ? WheelAudioComponent->SetVolumeMultiplier(0.1f) : WheelAudioComponent->SetVolumeMultiplier(0.0f);
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
	
		if (ChaosWheeledVehicleMovementComponent->GetCurrentGear() != CurrentGear) {

			//Play Exhaust Pops
			ExhaustAudioComponent->Play();
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExhaustPopParticle, ExhaustAudioComponent->GetComponentLocation(), ExhaustAudioComponent->GetComponentRotation(), FVector(0.2, 0.2, 0.2));

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Name: %s"), *ExhaustAudioComponent->GetComponentLocation().ToString()));
			CurrentGear = ChaosWheeledVehicleMovementComponent->GetCurrentGear();
		}
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
