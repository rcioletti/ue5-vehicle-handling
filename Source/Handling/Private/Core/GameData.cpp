#include "Core/GameData.h"

UGameData* UGameData::INSTANCE;

UGameData::UGameData()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		MapsTable_BP(TEXT("DataTable'/Game/Data/DT_MapData.DT_MapData'"));

	SetMapsTable(MapsTable_BP.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable>
		CarsTable_BP(TEXT("DataTable'/Game/Data/DT_CarData.DT_CarData'"));

	SetCarsTable(CarsTable_BP.Object);
}


UGameData* UGameData::GetInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = NewObject<UGameData>();
	}

	return INSTANCE;
}

TArray<FMapData*> UGameData::GetMaps()
{
	TArray<FMapData*> Maps;
	GetMapsTable()->GetAllRows<FMapData>(TEXT("Test"), Maps);
	return Maps;
}

TArray<FCarData*> UGameData::GetCars()
{
	TArray<FCarData*> Cars;
	GetCarsTable()->GetAllRows<FCarData>(TEXT("Test"), Cars);
	return Cars;
}
