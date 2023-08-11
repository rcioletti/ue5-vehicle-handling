// Fill out your copyright notice in the Description page of Project Settings.


#include "SPRaceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

ASPRaceGameMode::ASPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ARaceCarPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerController> myControllerOb(TEXT("Blueprint'/Game/Blueprints/VehiclePlayerController.VehiclePlayerController_C'"));
	auto myControllerClass = myControllerOb.Class;

	//PlayerControllerClass = AShooterPlayerController::StaticClass();
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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARaceCarPawn::StaticClass(), Cars);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PathBP, PathArray);

	if (!PathArray.IsEmpty()) {
		Path = PathArray[0];
	}
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

		if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("First Car Index %s"), *FString::FromInt(FirstCarIndex)));
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Progress %f Position %s Position in Car %s"), FMath::Max(CurrentPosition), *FString::FromInt(i + 1), *FString::FromInt(FirstCar->CurrentPosition)));
			

		CurrentPosition[MaxCarIndex] = -1.0f;
	}
}
