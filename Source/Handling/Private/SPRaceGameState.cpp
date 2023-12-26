// Fill out your copyright notice in the Description page of Project Settings.


#include "SPRaceGameState.h"
#include <Components\SplineComponent.h>
#include <Kismet\GameplayStatics.h>
#include <RacePlayerState.h>

ASPRaceGameState::ASPRaceGameState() {

	GM = Cast<ASPRaceGameMode>(UGameplayStatics::GetGameMode(this));

	//PrimaryActorTick.bStartWithTickEnabled = true;
	//PrimaryActorTick.bCanEverTick = true;
}

void ASPRaceGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASPRaceGameState::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		FuzeTimerHandle, // handle to cancel timer at a later time
		this, // the owning object
		&ASPRaceGameState::SortCarPosition, // function to call on elapsed
		0.5f, // float delay until elapsed
		true);
}

void ASPRaceGameState::SortCarPosition()
{

	TArray<ARaceCarPawn*> Cars = GM->Cars;
	USplineComponent* Spline = GM->Path->FindComponentByClass<USplineComponent>();


	for (AActor* CarActor : Cars)
	{
		ARaceCarPawn* Car = Cast<ARaceCarPawn>(CarActor);

		CarsCurrentPositionInTrack.FindOrAdd(Car) = Spline->FindInputKeyClosestToWorldLocation(Car->GetMesh()->GetComponentLocation()) + Car->CurrentLap * 20;
	}

	CarsCurrentPositionInTrack.ValueSort([](const float& A, const float& B) {
		return	A > B;
		});

	int Position = 1;

	for (auto& e : CarsCurrentPositionInTrack)
	{

		e.Key->CurrentPosition = Position;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Position: %s"), *FString::FromInt(Position)));

		Position++;
	}

	TArray<ARaceCarPawn*> RaceCars;

	for (auto e : Cars) {
		ARaceCarPawn* Car = Cast<ARaceCarPawn>(e);
		RaceCars.Add(Car);
	}

	CarsOrderedByCurrentPosition = SortAllCarsByPosition(RaceCars);
}

TArray<ARaceCarPawn*> ASPRaceGameState::SortAllCarsByPosition(TArray<ARaceCarPawn*> CarsUnordered)
{
	TArray<ARaceCarPawn*> CarsOrdered = CarsUnordered;

	CarsOrdered.Sort(ASPRaceGameState::SortPredicate);

	return CarsOrdered;

}

inline bool ASPRaceGameState::SortPredicate(const ARaceCarPawn& itemA, const ARaceCarPawn& itemB)
{
	return(itemA.CurrentPosition < itemB.CurrentPosition);
}