// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <RaceCarPawn.h>
#include <GameFramework\PlayerStart.h>
#include "SPRaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ASPRaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ASPRaceGameMode();

	virtual void BeginPlay() override;
	
	TArray<FTransform> FindAllPlayerStart();

	TArray<AActor*> AllPlayerStartActor;

	TArray<FString> RandomBotNames = {TEXT("Kazuya"),TEXT("Aoki"),TEXT("Ogawa"),TEXT("Kazama"),
		TEXT("Oshima"),TEXT("Nishizawa"),TEXT("Noda"),TEXT("Nobunaga"),TEXT("Matsuda"),
		TEXT("Mitsui"),TEXT("Hattori"),TEXT("Hane"),TEXT("Hoshino"),TEXT("Yoshi"),TEXT("Miura"),
		TEXT("Suzuki"),TEXT("Sato"),TEXT("Tajima"),TEXT("Tachikawa"),TEXT("Takashi"),
		TEXT("Nakajima"), TEXT("Nagasaka"),TEXT("Mihara"),TEXT("Ohara"),TEXT("Nakaya"),
		TEXT("Nakayama"),TEXT("Sasaki"),TEXT("Kotaka"),TEXT("Kogure"),TEXT("Kurosawa"), TEXT("Koyama") };

public:

	UFUNCTION(BLueprintCallable)
	void SpawnPlayer(APlayerController* PlayerController);

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TArray<ARaceCarPawn*> Cars;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<AActor> PathBP;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<ARaceCarPawn> PlayerCar;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<ARaceCarPawn> AICar;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	AActor* Path;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 GameLaps;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 MaxBots;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 RacePayout;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	bool bHasRaceStarted = false;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	bool isTimeTrial;
};
