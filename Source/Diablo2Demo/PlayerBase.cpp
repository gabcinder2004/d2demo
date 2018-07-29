// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBase.h"


void APlayerBase::DrinkHpPotion() {
	UE_LOG(LogTemp, Warning, TEXT("YoCustom"));
	for (int i = 0; i < 4; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("YoCustom"));
		_sleep(500);
	}
}

