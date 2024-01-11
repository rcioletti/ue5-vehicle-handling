#include "Core/GameData.h"

UGameData::UGameData()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		MapsTable_BP(TEXT("DataTable'/Game/Data/DT_Map.DT_Map'"));

	SetMapsTable(MapsTable_BP.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable>
		CarsTable_BP(TEXT("DataTable'/Game/Data/DT_Car.DT_Car'"));

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

TArray<FMaps*> UGameData::GetMaps()
{
	TArray<FMaps*> Maps;
	GetMapsTable()->GetAllRows<FMaps>(TEXT("Test"), Maps);
	return Maps;
}

TArray<FCars*> UGameData::GetCars()
{
	TArray<FCars*> Cars;
	GetMapsTable()->GetAllRows<FCars>(TEXT("Test"), Cars);
	return Cars;
}
