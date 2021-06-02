// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "PawnBaseTank.h"
#include "MyPawnAllyTank.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent; 

UCLASS()
class TOONTANKS_API AMyPawnAllyTank : public APawnBaseTank
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	APlayerController* PlayerControllerRef;

	FVector MoveDirection;
	FQuat RotationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0F;

	bool bIsPlayerAlive = true;

	void CalculateMovementInput(float Value);
	void CalculateRotationInput(float Value);

	void Move();
	void Rotate();
	
public:

	AMyPawnAllyTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	
};
