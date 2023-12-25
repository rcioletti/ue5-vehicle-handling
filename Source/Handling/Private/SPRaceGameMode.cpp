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

void ASPRaceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SortCarPosition();
}

void ASPRaceGameMode::BeginPlay()
{
	Super::BeginPlay();

	URaceGameInstance* GameInstance = Cast<URaceGameInstance>(GetGameInstance());

	if (GameInstance->SelectedCar != nullptr) {
		PlayerCar = GameInstance->SelectedCar;
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
		const FVector SpawnLocation = AllPlayerStartTransform[0].GetLocation();
		const FRotator SpawnRotation = AllPlayerStartTransform[0].Rotator();
		ARaceCarPawn* SpawnedPlayerCar = Cast<ARaceCarPawn>(GetWorld()->SpawnActor(PlayerCar, &SpawnLocation, &SpawnRotation, SpawnParams));
		PlayerController->Possess(SpawnedPlayerCar);
	}

	if (AICar) {
		if (AllPlayerStartTransform.Num() == 1 + MaxBots) {
			for (int32 i = 1; i < MaxBots + 1; i++)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				const FVector SpawnLocationBot = AllPlayerStartTransform[i].GetLocation();
				const FRotator SpawnRotationBot = AllPlayerStartTransform[i].Rotator();
				ARaceCarPawn* SpawnedBot = Cast<ARaceCarPawn>(GetWorld()->SpawnActor(AICar, &SpawnLocationBot, &SpawnRotationBot, SpawnParams));
				SpawnedBot->Name = "Bot ";
				SpawnedBot->Name.Append(FString::FromInt(i));
			}
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARaceCarPawn::StaticClass(), Cars);
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

void ASPRaceGameMode::SortCarPosition()
{

	for (AActor* CarActor : Cars)
	{
		ARaceCarPawn* Car = Cast<ARaceCarPawn>(CarActor);

		USplineComponent* Spline = Path->FindComponentByClass<USplineComponent>();

		CarsCurrentPositionInTrack.FindOrAdd(Car) = Spline->FindInputKeyClosestToWorldLocation(Car->GetMesh()->GetComponentLocation()) + Car->CurrentLap * 20;
	}

	CarsCurrentPositionInTrack.ValueSort([](const float& A, const float& B) {
		return	A > B;
	});

	int Position = 1;

	for (auto& e : CarsCurrentPositionInTrack)
	{

		e.Key->CurrentPosition = Position;

		Position++;
	}

	TArray<ARaceCarPawn*> RaceCars;

	for (auto e : Cars) {
		ARaceCarPawn* Car = Cast<ARaceCarPawn>(e);
		RaceCars.Add(Car);
	}

	CarsOrderedByCurrentPosition = SortAllCarsByPosition(RaceCars);
}

TArray<ARaceCarPawn*> ASPRaceGameMode::SortAllCarsByPosition(TArray<ARaceCarPawn*> CarsUnordered)
{
	TArray<ARaceCarPawn*> CarsOrdered = CarsUnordered;

	CarsOrdered.Sort(ASPRaceGameMode::SortPredicate);

	return CarsOrdered;

}

inline bool ASPRaceGameMode::SortPredicate(const ARaceCarPawn& itemA, const ARaceCarPawn& itemB)
{
	return(itemA.CurrentPosition < itemB.CurrentPosition);
}
