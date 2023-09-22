// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <RaceCarPawn.h>
#include "Engine/DataTable.h"
#include "GameStructs.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCars : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	USkeletalMesh* CarSkeletalMesh;

	UPROPERTY(BlueprintReadWrite)
	ARaceCarPawn* CarPawn;

	UPROPERTY(BlueprintReadWrite)
	UTexture2D* CarThumbnail;

	UPROPERTY(BlueprintReadWrite)
	FName CarModelName;

	UPROPERTY(BlueprintReadWrite)
	FName CarMakeName;

	UPROPERTY(BlueprintReadWrite)
	int32 Power;

	UPROPERTY(BlueprintReadWrite)
	int32 Torque;

	UPROPERTY(BlueprintReadWrite)
	int32 TopSpeed;

	UPROPERTY(BlueprintReadWrite)
	int32 Weigth;

};

USTRUCT(BlueprintType)
struct FMaps : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* MapThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName;

};

USTRUCT(BlueprintType)
struct FCarCustomizations : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARaceCarPawn> Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor CarColor;

};