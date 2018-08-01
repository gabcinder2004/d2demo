// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBaseV2.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

void APlayerBaseV2::BeginPlay() {
	ACharacter::BeginPlay();
	SetSpeed(RunSpeed);
	Health = MaxHealth;
	Mana = MaxMana;
	Stamina = MaxStamina;
}

void APlayerBaseV2::Tick(float DeltaTime)
{
	ACharacter::Tick(DeltaTime);

	if (CheckAlive()) {
		if (EnemyTargeted && WithinAttackRange(EnemyTarget)) {
			UCharacterMovementComponent* Movement = GetCharacterMovement();
			Movement->StopMovementImmediately();
			Moving = false;
			Attacking = true;		
		}
		Moving = MovingCheck();
		AdjustStaminaAndSpeed();
		if (RightClickHold) {
			//Further Stuff Needed
		}

	}
}

bool APlayerBaseV2::MovingCheck() {
	FVector velocity = GetVelocity();
	return velocity.GetAbsMax() > 0;
}

/*
	When Enemy Clicked From a Distance, and you stop within Range
*/
//void APlayerBaseV2::CheckIfShouldAttackWhenStopped() {
//	if (EnemyTargeted && WithinAttackRange(EnemyTarget) && !Attacking) {
//		Attacking = true;
//	}
//}

void APlayerBaseV2::RotateToTargetLocation(FVector location) {
	auto Direction = GetActorLocation() - location;
	FRotator Rot = FRotationMatrix::MakeFromX(Direction).Rotator();
	auto time = GetWorld()->GetRealTimeSeconds();
	auto interpRot = FMath::RInterpTo(GetActorRotation(), Rot, time, 20.0);
	SetActorRotation(interpRot);
}


bool APlayerBaseV2::WithinAttackRange(AEnemyBaseV2* enemyTargeted) {
	if (enemyTargeted) {
		return GetDistanceTo(enemyTargeted) <= AttackRange;
	}
	else {
		return false;
	}
}

void APlayerBaseV2::SetSpeed(float speed) {
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = RunSpeed;
}

void APlayerBaseV2::AdjustStaminaAndSpeed() {
	if (Moving) {
		Stamina = Stamina - DecrementStaminaRate;
		if (Stamina > 0) {
			SetSpeed(RunSpeed);
		}
		else {
			SetSpeed(WalkSpeed);
		}
	}
	else {
		Stamina = Stamina + IncrementStaminaRate;
	}
}

bool APlayerBaseV2::CheckAlive() {
	if (!Alive) {
		return Alive;
	}
	if (Health <= 0) {
		Alive = false;
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->DisableMovement();
		return Alive;
	}
	Alive = true;
	return Alive;
}


