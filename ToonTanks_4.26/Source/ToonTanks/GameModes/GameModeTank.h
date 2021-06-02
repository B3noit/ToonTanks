// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ToonTanks/Pawns/MyPawnAllyTank.h"
#include "ToonTanks/Pawns/PawnEnemyTurret.h"
#include "ToonTanks/PlayerController/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeTank.generated.h"

/**
 * 
 */

class AMyPawnAllyTank;
class APawnEnemyTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API AGameModeTank : public AGameModeBase
{
	GENERATED_BODY()

private:

	AMyPawnAllyTank* PlayerTank;
	int32 TargetTurrets = 0;
	APlayerControllerBase* PlayerControllerRef;

	int32 GetTargetTurretCount();

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);



public:

	void ActorDied(AActor* DeadActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop");
	int32 StartDelay = 4;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};