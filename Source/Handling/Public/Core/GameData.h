#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Player/RaceCarPawn.h>
#include "Engine/DataTable.h"
#include "GameData.generated.h"

UENUM(BlueprintType)
enum class EGameType : uint8 {
	SINGLEPLAYER,
	TIMETRIAL,
	MULTIPLAYER,
};

USTRUCT(BlueprintType)
struct FCarData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	USkeletalMesh* CarSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	TSubclassOf<class ARaceCarPawn> CarPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	UTexture2D* CarThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	FName CarModelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	FName CarMakeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Power = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Torque = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 TopSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Acceleration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Weigth = 0;

};

USTRUCT(BlueprintType)
struct FMapData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	UTexture2D* MapThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	int32 MinLaps = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	int32 MaxLaps = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	int32 LapPayout = 0;

};

USTRUCT(BlueprintType)
struct FCarCustomizations : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARaceCarPawn> Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor CarColor = FLinearColor::Black;

};

UCLASS()
class HANDLING_API UGameData : public UObject
{
	GENERATED_BODY()

public: 

	UGameData();

	TArray<FMapData*> GetMaps();
	TArray<FCarData*> GetCars();

	UDataTable* GetMapsTable() { return MapsTable; }
	void SetMapsTable(UDataTable* DataTableBP) { MapsTable = DataTableBP; }

	UDataTable* GetCarsTable() { return CarsTable; }
	void SetCarsTable(UDataTable* DataTableBP) { CarsTable = DataTableBP; }

private:
	UDataTable* MapsTable;
	UDataTable* CarsTable;
};
