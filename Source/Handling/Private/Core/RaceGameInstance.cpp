// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RaceGameInstance.h"
#include <MoviePlayer\Public\MoviePlayer.h>
#include "Runtime/UMG/Public/UMG.h"
#include "Kismet/GameplayStatics.h"

URaceGameInstance::URaceGameInstance() {

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Game Instance Initialized")));
	static ConstructorHelpers::FClassFinder<UUserWidget> loadScreenWidgetPath(TEXT("WidgetBlueprint'/Game/UI/UI_LoadScreen.UI_LoadScreen_C'"));

	if (loadScreenWidgetPath.Class != nullptr) { LoadScreenWidget = loadScreenWidgetPath.Class; }
}

void URaceGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &URaceGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &URaceGameInstance::EndLoadingScreen);
}

void URaceGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer()) {
		FLoadingScreenAttributes LoadScreenAtt;
		LoadScreenAtt.bAutoCompleteWhenLoadingCompletes = false;

		if (UseMovies) {
			LoadScreenAtt.MoviePaths = StringPaths;
		}

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LoadScreenWidget);
		LoadScreenAtt.WidgetLoadingScreen = Widget->TakeWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadScreenAtt);
	}
}

void URaceGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
}

void URaceGameInstance::LoadGame()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0);
	SaveGameObject = Cast<URaceSaveGame>(LoadedGame);

	if (!SaveGameObject) {

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Creating new save game")));

		SaveGameObject = Cast<URaceSaveGame>(UGameplayStatics::CreateSaveGameObject(URaceSaveGame::StaticClass()));

		const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);
	}
}

void URaceGameInstance::SaveGame()
{
	const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);
}

void URaceGameInstance::SetCarCustomizations(FCarCustomizations CarMod)
{
	bool bWasSet = false;

	for (int i = 0; i < SaveGameObject->CarMods.Num(); i++) {
		
		if (SaveGameObject->CarMods[i].Car == CarMod.Car) {
			
			bWasSet = true;

			SaveGameObject->CarMods.RemoveAt(i);
			SaveGameObject->CarMods.Insert(CarMod, i);

			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Set custom mods")));
		}
	}
		
	if (!bWasSet) {

		SaveGameObject->CarMods.Add(CarMod);

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Set custom mods added new car")));
	}

	SaveGame();
}

FCarCustomizations URaceGameInstance::GetCarCustomizations(TSubclassOf<ARaceCarPawn> CarPawnReference)
{
	if (SaveGameObject != NULL) {
		for (int i = 0; i < SaveGameObject->CarMods.Num(); i++) {

			if (SaveGameObject->CarMods[i].Car == CarPawnReference) {

				return SaveGameObject->CarMods[i];
			}
		}
	}

	return FCarCustomizations();
}

void URaceGameInstance::AddMoney(int32 Money)
{
	SaveGameObject->Money += Money;
}

void URaceGameInstance::RemoveMoney(int32 Money)
{
	SaveGameObject->Money -= Money;
}

bool URaceGameInstance::SetNewBestTime(float Time, FString MapName)
{
	if (Time < SaveGameObject->BestLapTime) {
		
		SaveGameObject->BestLapTime = Time;

		return true;
	}

	return false;
}
