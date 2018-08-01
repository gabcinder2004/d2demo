// Fill out your copyright notice in the Description page of Project Settings.

#include "DiabloControllerV2.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Diablo2DemoCharacter.h"
#include "Engine/World.h"
#include "EnemyBase.h"
#include "PlayerBase.h"

ADiabloControllerV2::ADiabloControllerV2()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADiabloControllerV2::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ADiabloControllerV2::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADiabloControllerV2::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ADiabloControllerV2::OnSetDestinationReleased);
	InputComponent->BindAction("TargetRightClick", IE_Pressed, this, &ADiabloControllerV2::OnRightClickPressed);
	InputComponent->BindAction("TargetRightClick", IE_Released, this, &ADiabloControllerV2::OnRightClickReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADiabloControllerV2::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ADiabloControllerV2::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ADiabloControllerV2::OnResetVR);
}

void ADiabloControllerV2::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADiabloControllerV2::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ADiablo2DemoCharacter* MyPawn = Cast<ADiablo2DemoCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under tactorhe mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Pawn, false, Hit);
		auto ActorHit = Hit.GetActor();
		if (ActorHit) {
			UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
		}

		auto result = Cast<AEnemyBase>(ActorHit);

		FVector moveSpot;
		bool move = true;
		APawn* const MyPawn = GetPawn();
		//auto player = Cast<APlayerBase>(MyPawn);
		//if (result) {
		//	auto pawnVector = player->GetActorLocation();
		//	player->OnMobTargeted(result);
		//	auto hitLocation = result->GetActorLocation();
		//	moveSpot = Hit.ImpactPoint;
		//	/*		float initialDistance = FVector::Dist(hitLocation, pawnVector);
		//	UE_LOG(LogTemp, Warning, TEXT("Init: %f"), initialDistance);
		//	if (initialDistance > 90.0f) {
		//	moveSpot = (hitLocation + pawnVector) / 2;
		//	float Distance = FVector::Dist(hitLocation, moveSpot);
		//	while (Distance > 90.0f) {
		//	moveSpot = (hitLocation + moveSpot) / 2;
		//	Distance = FVector::Dist(hitLocation, moveSpot);
		//	}
		//	}
		//	else {
		//	UE_LOG(LogTemp, Warning, TEXT("No move"));
		//	move = false;
		//	}*/
		//}
		//else {
			moveSpot = Hit.ImpactPoint;
			//player->OnMobUnTarget();
		//}

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(moveSpot);
		}
	}
}

void ADiabloControllerV2::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);

	if (HitResult.bBlockingHit)
	{
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ADiabloControllerV2::SetNewMoveDestination(const FVector DestLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Poop %s"))
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);

		if ((Distance > 50.0f))
		{
			UE_LOG(LogTemp, Warning, TEXT("HERE"));
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ADiabloControllerV2::OnRightClickPressed()
{
	APawn* const MyPawn = GetPawn();
	auto player = Cast<APlayerBase>(MyPawn);
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);
	auto ActorHit = Hit.GetActor();
	/*if (ActorHit) {
		player->OnRightMouseClicked(ActorHit, Hit.ImpactPoint);
	}
	else {
		player->OnRightMouseClicked(NULL, Hit.ImpactPoint);
	}*/
}

void ADiabloControllerV2::OnRightClickReleased()
{
	APawn* const MyPawn = GetPawn();
	/*auto player = Cast<APlayerBase>(MyPawn);
	player->OnRightMouseReleased();*/
}

void ADiabloControllerV2::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ADiabloControllerV2::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	// Can use this to know when mouse released
	bMoveToMouseCursor = false;
}
