// Fill out your copyright notice in the Description page of Project Settings.


#include "SPRaceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

ASPRaceGameMode::ASPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = nullptr;

	static ConstructorHelpers::FClassFinder<APlayerController> myControllerOb(TEXT("Blueprint'/Game/Blueprints/VehiclePlayerController.VehiclePlayerController_C'"));
	auto myControllerClass = myControllerOb.Class;

	PlayerControllerClass = myControllerClass;
}

void ASPRaceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SortCarPosition();
}

void ASPRaceGameMode::BeginPlay()
{
	Super::BeginPlay();

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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARaceCarPawn::StaticClass(), Cars);
}

TArray<FTransform> ASPRaceGameMode::FindAllPlayerStart()
{
	TArray<FTransform> AllPlayerStartTransform;

	for (AActor* PlayerStartActor : AllPlayerStartActor)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);
		AllPlayerStartTransform.Add(PlayerStart->GetTransform());
	}

	return AllPlayerStartTransform;
}

void ASPRaceGameMode::SortCarPosition()
{
	CurrentPosition.Empty();

	int32 Index = 0;

	for (AActor* CarActor : Cars)
	{
		ARaceCarPawn* Car = Cast<ARaceCarPawn>(CarActor);

		USplineComponent* Spline = Path->FindComponentByClass<USplineComponent>();

		CurrentPosition.Add(Spline->FindInputKeyClosestToWorldLocation(Car->GetMesh()->GetComponentLocation()));

		CurrentPosition[Index] = Car->CurrentLap * 20 + CurrentPosition[Index];

		Index++;
	}

	for (int32 i = 0; i < Cars.Num(); i++)
	{
		int32 MaxCarIndex;
		FMath::Max(CurrentPosition, &MaxCarIndex);

		ARaceCarPawn* FirstCar = Cast<ARaceCarPawn>(Cars[MaxCarIndex]);
		FirstCar->CurrentPosition = i + 1;

		//if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("First Car Index %s"), *FString::FromInt(FirstCarIndex)));
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Progress %f Position %s Position in Car %s"), FMath::Max(CurrentPosition), *FString::FromInt(i + 1), *FString::FromInt(FirstCar->CurrentPosition)));
			

		CurrentPosition[MaxCarIndex] = -1.0f;
	}
}
