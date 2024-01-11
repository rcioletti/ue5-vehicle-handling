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
struct FCars : public FTableRowBase
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
	int32 Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Torque;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 TopSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Car Data")
	int32 Weigth;

};

USTRUCT(BlueprintType)
struct FMaps : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* MapThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinLaps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLaps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LapPayout;

};

USTRUCT(BlueprintType)
struct FCarCustomizations : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARaceCarPawn> Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor CarColor;

};

UCLASS()
class HANDLING_API UGameData : public UObject
{
	GENERATED_BODY()

public: 

	UGameData();

	static UGameData* GetInstance();

	TArray<FMaps*> GetMaps();
	TArray<FCars*> GetCars();

	UDataTable* GetMapsTable() { return MapsTable; }
	void SetMapsTable(UDataTable* DataTableBP) { MapsTable = DataTableBP; }

	UDataTable* GetCarsTable() { return CarsTable; }
	void SetCarsTable(UDataTable* DataTableBP) { CarsTable = DataTableBP; }

private:
	inline static UGameData* INSTANCE;
	UDataTable* MapsTable;
	UDataTable* CarsTable;
};
