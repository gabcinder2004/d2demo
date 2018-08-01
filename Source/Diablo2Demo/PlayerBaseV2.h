// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Diablo2DemoCharacter.h"
#include "EnemyBaseV2.h"
#include "PlayerBaseV2.generated.h"

/**
 * 
 */
UCLASS()
class DIABLO2DEMO_API APlayerBaseV2 : public ADiablo2DemoCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	bool MovingCheck();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, category = "AttackEvent")
		void OnMobTargeted(AEnemyBase* targetEnemy);
	UFUNCTION(BlueprintImplementableEvent, category = "AttackEvent")
		void OnMobUnTarget();
	UFUNCTION(BlueprintImplementableEvent, category = "RightAttackEvent")
		void OnRightMouseClicked(AActor* targetEnemy, FVector vector);
	UFUNCTION(BlueprintImplementableEvent, category = "RightAttackEvent")
		void OnRightMouseReleased();
	//UFUNCTION(BluePrintCallable)
	//	void CheckIfShouldAttackWhenStopped();
	UFUNCTION(BluePrintCallable)
		bool WithinAttackRange(AEnemyBaseV2* enemyTarget);
	UFUNCTION(BluePrintCallable)
		void AdjustStaminaAndSpeed();
	UFUNCTION(BluePrintCallable)
		void SetSpeed(float speed);
	UFUNCTION(BluePrintCallable)
		bool CheckAlive();
	UFUNCTION(BluePrintCallable)
		void RotateToTargetLocation(FVector location);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mana = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecrementStaminaRate = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IncrementStaminaRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 200.f;


/*Maintaining State Fields*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Moving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnemyTargeted = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Attacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Alive = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RightClickHold = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEnemyBaseV2* EnemyTarget;
};
