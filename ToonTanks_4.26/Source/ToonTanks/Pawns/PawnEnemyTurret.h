// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "MyPawnAllyTank.h"


#include "CoreMinimal.h"
#include "PawnBaseTank.h"
#include "PawnEnemyTurret.generated.h"

class AMyPawnAllyTank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnEnemyTurret : public APawnBaseTank
{
	GENERATED_BODY()


private:

	void CheckFireCondition();

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	AMyPawnAllyTank* PlayerPawn;

	float ReturnDistanceToPlayer();

	float FireRange = 500.0f;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
