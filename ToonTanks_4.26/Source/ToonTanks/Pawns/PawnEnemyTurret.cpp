// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnEnemyTurret.h"


// Called when the game starts or when spawned
void APawnEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnEnemyTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<AMyPawnAllyTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}


// Called every frame
void APawnEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || ReturnDistanceToPlayer() < FireRange)
	{//If the turret has the player in range, it's gonna rotate towards the player.
		RotateTurretFunction(PlayerPawn->GetActorLocation());
	}


}


void APawnEnemyTurret::CheckFireCondition()
{
	//Checking if the player Exist and is not dead
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
		//UE_LOG(LogTemp, Warning, TEXT("Fire Condition fail"));
	}

	//Checking if the player is in the range of the turret
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
		//FireTowards the player
		//UE_LOG(LogTemp, Warning, TEXT("Fire Condition Succes"));
	}
}


float APawnEnemyTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

	return Distance;
}

void APawnEnemyTurret::HandleDestruction()
{
	//Call base pawn class HandleDestruction to play effects.
	Super::HandleDestruction();
	Destroy();
}