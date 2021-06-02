// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ToonTanks/GameModes/GameModeTank.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AGameModeTank;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private: 



	float Health = 0.0f;

	AGameModeTank* GameModeRef;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultHealth = 100.0f;
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
		
};
