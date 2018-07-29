// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Diablo2DemoCharacter.h"
#include "PlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class DIABLO2DEMO_API APlayerBase : public ADiablo2DemoCharacter
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, category = "AttackEvent")
	void OnMobTargeted(AEnemyBase* targetEnemy);
	UFUNCTION(BlueprintImplementableEvent, category = "AttackEvent")
		void OnMobUnTarget();
	UFUNCTION(BlueprintImplementableEvent, category = "RightAttackEvent")
		void OnRightMouseClicked(AActor* targetEnemy, FVector vector);
	UFUNCTION(BlueprintImplementableEvent, category = "RightAttackEvent")
		void OnRightMouseReleased();
	UFUNCTION(BlueprintCallable)
		void DrinkHpPotion();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health = 200;
	
	
	
	
};
