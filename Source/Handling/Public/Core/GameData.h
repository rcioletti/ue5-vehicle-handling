#pragma once

#include "CoreMinimal.h"
#include "GameData.generated.h"

UENUM(BlueprintType)
enum class EGameType : uint8 {
	SINGLEPLAYER,
	TIMETRIAL,
	MULTIPLAYER,
};
