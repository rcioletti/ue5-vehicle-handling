// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "LobbyShowcaseCar.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ALobbyShowcaseCar : public AActor
{
	GENERATED_BODY()
	
	ALobbyShowcaseCar();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

public:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CarSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_SelectedCar)
	USkeletalMesh* CarMesh;

	UFUNCTION()
	void OnRep_SelectedCar();
};
