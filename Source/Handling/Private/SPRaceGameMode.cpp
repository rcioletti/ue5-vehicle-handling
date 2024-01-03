// Fill out your copyright notice in the Description page of Project Settings.


#include "SPRaceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
#include <RaceGameInstance.h>

ASPRaceGameMode::ASPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = nullptr;

	//static ConstructorHelpers::FClassFinder<APlayerController> myControllerOb(TEXT("/Game/Core/VehiclePlayerController.VehiclePlayerController_C"));
	//auto myControllerClass = myControllerOb.Class;

	//PlayerControllerClass = myControllerClass;
}

void ASPRaceGameMode::BeginPlay()
{
	Super::BeginPlay();

	URaceGameInstance* GameInstance = Cast<URaceGameInstance>(GetGameInstance());

	if (GameInstance->SelectedCar != nullptr) {
		PlayerCar = GameInstance->SelectedCar;
	}

	if (GameInstance->NumberOfLaps != 0) {
		GameLaps = GameInstance->NumberOfLaps;
	}

	if (GameInstance->isTimeTrial != NULL) {
		isTimeTrial = GameInstance->isTimeTrial;
	}

	TArray<AActor*> PathArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PathBP, PathArray);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllPlayerStartActor);

	if (!PathArray.IsEmpty()) {
		Path = PathArray[0];
	}
}

void ASPRaceGameMode::SpawnPlayer(APlayerController* PlayerController)
{
	TArray<FTransform> AllPlayerStartTransform = FindAllPlayerStart();

	if (PlayerController->GetPawn() != nullptr) {
		PlayerController->GetPawn()->Destroy();
	}
	
	if (PlayerCar) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PlayerController;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FVector SpawnLocation = AllPlayerStartTransform[0].GetLocation() - FVector(0,0, 90);
		const FRotator SpawnRotation = AllPlayerStartTransform[0].Rotator();
		ARaceCarPawn* SpawnedPlayerCar = Cast<ARaceCarPawn>(GetWorld()->SpawnActor(PlayerCar, &SpawnLocation, &SpawnRotation, SpawnParams));
		PlayerController->Possess(SpawnedPlayerCar);

		SpawnedPlayerCar->ChaosWheeledVehicleMovementComponent->SetHandbrakeInput(1.0f);

		Cars.Add(SpawnedPlayerCar);
	}

	if (!isTimeTrial) {

		if (AICar) {

			if (AllPlayerStartTransform.Num() == 1 + MaxBots) {
				for (int32 i = 1; i < MaxBots + 1; i++)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					const FVector SpawnLocationBot = AllPlayerStartTransform[i].GetLocation() - FVector(0, 0, 90);
					const FRotator SpawnRotationBot = AllPlayerStartTransform[i].Rotator();
					ARaceCarPawn* SpawnedBot = Cast<ARaceCarPawn>(GetWorld()->SpawnActor(AICar, &SpawnLocationBot, &SpawnRotationBot, SpawnParams));
					SpawnedBot->Name = RandomBotNames[FMath::RandRange(0, RandomBotNames.Num())];

					SpawnedBot->ChaosWheeledVehicleMovementComponent->SetHandbrakeInput(1.0f);

					Cars.Add(SpawnedBot);
				}
			}
		}
	}
}

TArray<FTransform> ASPRaceGameMode::FindAllPlayerStart()
{
	TArray<FTransform> AllPlayerStartTransform;
	
	if (AllPlayerStartActor.Num() <= 0) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllPlayerStartActor);
	}

	for (AActor* PlayerStartActor : AllPlayerStartActor)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);
		AllPlayerStartTransform.Add(PlayerStart->GetTransform());
	}

	return AllPlayerStartTransform;
}
