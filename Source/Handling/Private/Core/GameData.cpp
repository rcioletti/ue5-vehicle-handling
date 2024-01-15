#include "Core/GameData.h"

UGameData::UGameData()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		MapsTable_BP(TEXT("DataTable'/Game/Data/DT_MapData.DT_MapData'"));

	SetMapsTable(MapsTable_BP.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable>
		CarsTable_BP(TEXT("DataTable'/Game/Data/DT_CarData.DT_CarData'"));

	SetCarsTable(CarsTable_BP.Object);
}

TArray<FMapData*> UGameData::GetMaps()
{
	TArray<FMapData*> Maps;
	GetMapsTable()->GetAllRows<FMapData>(TEXT("Maps"), Maps);
	return Maps;
}

TArray<FCarData*> UGameData::GetCars()
{
	TArray<FCarData*> Cars;
	GetCarsTable()->GetAllRows<FCarData>(TEXT("Cars"), Cars);
	return Cars;
}
