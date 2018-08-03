// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendlyBase.h"


// Sets default values
AFriendlyBase::AFriendlyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFriendlyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFriendlyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFriendlyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFriendlyBase::A
