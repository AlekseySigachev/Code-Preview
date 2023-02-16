// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPMainGameMode.h"

#include "CPPPlayerController.h"
#include "CPPMainGameInstance.h"
#include "CPPPlayerPawn.h"
#include "CPPPlayerShip.h"
#include "Map/CPPOrbitalObject.h"
#include "Map/CPPSpaceObject_Station.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/CPPHUDWidget.h"


ACPPMainGameMode::ACPPMainGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ACPPPlayerController::StaticClass();
}
void ACPPMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ACPPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	StartStation = Cast<ACPPSpaceObject_Station>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPPSpaceObject_Station::StaticClass()));
	SpawnPlayers(StartStation);
	CreateHUDWidget();
	ReallocatePlayer();
	DrawScene();
}

void ACPPMainGameMode::PossessFirstPlayer()
{
	CurrentPlayer = Players[0];
	PlayerController->Possess(CurrentPlayer);
}
void ACPPMainGameMode::PossessNextPlayer()
{
	auto NextPlayerIndex = Players.Find(CurrentPlayer) + 1;
	if (NextPlayerIndex == -1) return;
	if (Players.Num() > NextPlayerIndex)
	{
		CurrentPlayer = Players[NextPlayerIndex];
		PlayerController->Possess(CurrentPlayer);
	}
	else
	{
		PossessFirstPlayer();
	}
}
void ACPPMainGameMode::CreateHUDWidget()
{
	HUD = CreateWidget<UCPPHUDWidget>(GetWorld(), HUDWidgetClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

void ACPPMainGameMode::ReallocatePlayer()
{
	for (int i = 0; i < Players.Num(); i++)
	{
		if (StartStation->Positions.IsEmpty()) return;
		Players[i]->SetActorLocation(StartStation->Positions[i]);
	}
}

void ACPPMainGameMode::ToggleInsideButton(ACPPSpaceObject* Target)
{
	HUD->GoInside->SetIsEnabled(Target->CanGoInside() && Target->bDiscovered);
}

int32 ACPPMainGameMode::GetPlayerQuantity()
{
	const auto GameInstance = Cast<UCPPMainGameInstance>(GetGameInstance());
	return GameInstance->PlayersQuantity;
}

void ACPPMainGameMode::SpawnPlayers(ACPPSpaceObject_Station* Station)
{
	for (int i = 1; i <= GetPlayerQuantity(); i++)
	{
		FActorSpawnParameters SpawnInfo;
		
		if (!PlayerClass) return;
		auto Player = GetWorld()->SpawnActor<ACPPPlayerPawn>(PlayerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		Players.Add(Player);
		Station->AddSpaceObjectToOrbit(Player->Ship);
		Player->CurrentStar = Station;
		auto PlayersShip = Cast<ACPPPlayerShip>(Player->Ship);
		PlayersShip->CurrentStar = Station;
	}
	PossessFirstPlayer();
	Station->CalcObjectsPositionsOnOrbit();
	Station->ReallocateObjectsOnOrbit();
}

void ACPPMainGameMode::MovePlayerToLocations(ACPPSpaceObject* Target)
{
	ToggleInsideButton(Target);
	CurrentPlayer->CurrentStar = Target;
	auto StarLocation = CurrentPlayer->CurrentStar->GetActorLocation();
	CurrentPlayer->SetActorLocation(FVector(StarLocation.X, StarLocation.Y, 0.0f));
	auto PlayerShip = Cast<ACPPPlayerShip>(CurrentPlayer->Ship);
	CheckAllowedDirection(CurrentPlayer->CurrentStar, PlayerShip->CurrentStar);
}

void ACPPMainGameMode::CheckAllowedDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar)
{
	auto DirectionList = ShipStar->GetAllowDirectionList();
	auto ReqDirection = GetRequieredDirection(PlayerStar, ShipStar);
	OnOffMoveButton(!(DirectionList.Find(ReqDirection) == -1));
}

int32 ACPPMainGameMode::GetRequieredDirection(ACPPSpaceObject* PlayerStar, ACPPSpaceObject* ShipStar)
{
	const int32 LDirection = 0;
	const auto &PlayerStarLocation = PlayerStar->GetActorLocation();
	const auto &ShipStarLocation = ShipStar->GetActorLocation();

	if (ShipStarLocation == PlayerStarLocation)
	{
		return LDirection;
	}
	else if (ShipStarLocation != PlayerStarLocation)
	{
		const auto& GridStep = PlayerStar->GetGridStep();
		auto LocationsSubtruct = ShipStarLocation - PlayerStarLocation;
		auto bHorizontalMove = LocationsSubtruct.X / GridStep != 0;
		auto bVerticalMove = LocationsSubtruct.Y / GridStep != 0;
		// запрещаем движение по диагонали
		if (bVerticalMove && bHorizontalMove)
		{
			return LDirection;
		}

		const bool bMoveInOneCell = FMath::Abs(LocationsSubtruct.X / GridStep) == 1
									|| FMath::Abs(LocationsSubtruct.Y / GridStep) == 1;

		// запрещаем если движение дальше одной ячейки 
		if (!bMoveInOneCell)
		{
			return LDirection;
		}

		if (bVerticalMove)
		{
			return TopDownMove(ShipStarLocation, PlayerStarLocation);
		}
		else if (bHorizontalMove)
		{
			return LeftRightMove(ShipStarLocation, PlayerStarLocation);
		}
	}
	// если чего то не учли - то запрещаем движение
	return LDirection;
}

int32 ACPPMainGameMode::TopDownMove(FVector ShipLoc, FVector PlayerLoc)
{
	if ((ShipLoc.Y - PlayerLoc.Y) < 0) 
	{
		return 1;
	}
	else
	{
		return 4;
	}
}

int32 ACPPMainGameMode::LeftRightMove(FVector ShipLoc, FVector PlayerLoc)
{
	if ((ShipLoc.X - PlayerLoc.X) > 0)
	{
		return 2;
	}
	else
	{
		return 8;
	}
}

void ACPPMainGameMode::OnOffMoveButton(bool Switch)
{
	HUD->Move->SetIsEnabled(Switch);
	if (Switch)
	{
		HUD->Move->SetBackgroundColor(FColor::Green);
	}
	else 
	{
		HUD->Move->SetBackgroundColor(FColor::Red);
	}
}

void ACPPMainGameMode::MoveShipToLocation()
{
	auto DestStar = CurrentPlayer->CurrentStar;
	auto PlayerShip = Cast<ACPPPlayerShip>(CurrentPlayer->Ship);
	auto SourceStar = PlayerShip->CurrentStar;
	PlayerShip->CurrentStar = DestStar;
	DestStar->AddSpaceObjectToOrbit(PlayerShip);
	DestStar->CalcObjectsPositionsOnOrbit();
	DestStar->ReallocateObjectsOnOrbit();
	SourceStar->RemoveObjectFromOrbit(PlayerShip);
	SourceStar->CalcObjectsPositionsOnOrbit();
	SourceStar->ReallocateObjectsOnOrbit();
	DestStar->DiscoverStar();
	ToggleInsideButton(DestStar);
}

void ACPPMainGameMode::DrawScene()
{
	FActorSpawnParameters SpawnInfo;

	MainScene = GetWorld()->SpawnActor<ACPPScene>(ACPPScene::StaticClass(), StartStation->GetActorLocation(), FRotator::ZeroRotator, SpawnInfo);
	auto SubSceneLocation = MainScene->GetActorLocation() + Delta;
	SubScene = GetWorld()->SpawnActor<ACPPScene>(ACPPScene::StaticClass(), SubSceneLocation, FRotator::ZeroRotator, SpawnInfo);
}
