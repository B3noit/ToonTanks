// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnAllyTank.h"


// Sets default values
AMyPawnAllyTank::AMyPawnAllyTank()
{
// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
PrimaryActorTick.bCanEverTick = true;

SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
SpringArm->SetupAttachment(RootComponent);

Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AMyPawnAllyTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

}

// Called every frame
void AMyPawnAllyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();

	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurretFunction(HitLocation);
	}
}

// Called to bind functionality to input
void AMyPawnAllyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawnAllyTank::CalculateMovementInput);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPawnAllyTank::CalculateRotationInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawnAllyTank::Fire);

}


void AMyPawnAllyTank::CalculateMovementInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void AMyPawnAllyTank::CalculateRotationInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds ;
	FRotator Rotation = FRotator(0, RotateAmount, 0);	
	RotationDirection = FQuat(Rotation); 
}

void AMyPawnAllyTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void AMyPawnAllyTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void AMyPawnAllyTank::HandleDestruction()
{
	//Call base pawn class HandleDestruction to play effects.
	Super::HandleDestruction();
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}


bool AMyPawnAllyTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}
