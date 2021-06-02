// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTank.h"

void AGameModeTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<AMyPawnAllyTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	HandleGameStart();
}

void AGameModeTank::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<AMyPawnAllyTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void AGameModeTank::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

void AGameModeTank::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	} 
	else if (APawnEnemyTurret* DestroyedTurret = Cast<APawnEnemyTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ActorDied triggered"));
}



int32 AGameModeTank::GetTargetTurretCount()
{
	TArray<AActor*>	TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnEnemyTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}