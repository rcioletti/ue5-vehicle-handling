// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RaceCarPawn.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ARaceCarPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	ARaceCarPawn();

public:

	UChaosWheeledVehicleMovementComponent* ChaosWheeledVehicleMovementComponent;

	bool IsSkidding;

	int32 CurrentGear;

	float CurrentWheelSkidVolume;

	void OnTireSkid();

	void PlayEngineSound();

	void OnGearChange();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ExhaustPopParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* WheelSmokeParticle;

	UFUNCTION(BLueprintCallable)
	void ClearTimer();

	UFUNCTION(BLueprintCallable)
	float GetCurrentBestTime();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int32 CurrentPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	float TimeCounter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	int32 CurrentLap = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	float NitrousContent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
	TArray<float> LapTimes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	UAudioComponent* EngineAudioComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	UAudioComponent* ExhaustAudioComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	UAudioComponent* WheelAudioComponent;

};
