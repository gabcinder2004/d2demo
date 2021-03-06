// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Diablo2DemoPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Diablo2DemoCharacter.h"
#include "Engine/World.h"
#include "EnemyBase.h"
#include "PlayerBase.h"

ADiablo2DemoPlayerController::ADiablo2DemoPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADiablo2DemoPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ADiablo2DemoPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADiablo2DemoPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ADiablo2DemoPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("TargetRightClick", IE_Pressed, this, &ADiablo2DemoPlayerController::OnRightClickPressed);
	InputComponent->BindAction("TargetRightClick", IE_Released, this, &ADiablo2DemoPlayerController::OnRightClickReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADiablo2DemoPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ADiablo2DemoPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ADiablo2DemoPlayerController::OnResetVR);
}

void ADiablo2DemoPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADiablo2DemoPlayerController::MoveToMouseCursor()
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
		auto player = Cast<APlayerBase>(MyPawn);
		if (result) {
			auto pawnVector = player->GetActorLocation();
			player->OnMobTargeted(result);
			auto hitLocation = result->GetActorLocation();
			moveSpot = Hit.ImpactPoint;
	/*		float initialDistance = FVector::Dist(hitLocation, pawnVector);
			UE_LOG(LogTemp, Warning, TEXT("Init: %f"), initialDistance);
			if (initialDistance > 90.0f) {
				moveSpot = (hitLocation + pawnVector) / 2;
				float Distance = FVector::Dist(hitLocation, moveSpot);
				while (Distance > 90.0f) {
					moveSpot = (hitLocation + moveSpot) / 2;
					Distance = FVector::Dist(hitLocation, moveSpot);
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("No move"));
				move = false;
			}*/
		}
		else {
			moveSpot = Hit.ImpactPoint;
			player->OnMobUnTarget();
		}

		if (Hit.bBlockingHit && move)
		{
			// We hit something, move there
			SetNewMoveDestination(moveSpot);
		}
	}
}

void ADiablo2DemoPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
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

void ADiablo2DemoPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Poop %s"))
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);

		if ((Distance > 50.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ADiablo2DemoPlayerController::OnRightClickPressed()
{
	APawn* const MyPawn = GetPawn();
	auto player = Cast<APlayerBase>(MyPawn);
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);
	auto ActorHit = Hit.GetActor();
	if (ActorHit) {
		player->OnRightMouseClicked(ActorHit, Hit.ImpactPoint);
	}
	else {
		player->OnRightMouseClicked(NULL, Hit.ImpactPoint);
	}
}

void ADiablo2DemoPlayerController::OnRightClickReleased()
{
	APawn* const MyPawn = GetPawn();
	auto player = Cast<APlayerBase>(MyPawn);
	player->OnRightMouseReleased();
}

void ADiablo2DemoPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ADiablo2DemoPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	// Can use this to know when mouse released
	bMoveToMouseCursor = false;
}
