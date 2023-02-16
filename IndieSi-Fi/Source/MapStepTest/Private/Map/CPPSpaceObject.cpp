// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/CPPSpaceObject.h"
#include "Math/UnrealMathUtility.h"

#include "Engine/DataTable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CPPMainGameMode.h"
#include "Map/CPPOrbitalObject.h"
#include "Map/CPPMapBuilder.h"
#include "MapStepTest/CustomStructs.h"

DEFINE_LOG_CATEGORY_STATIC(SpaceObjectLog, All, All);

ACPPSpaceObject::ACPPSpaceObject()

{
	PrimaryActorTick.bCanEverTick = true;
	
	const FVector Scale = FVector(0.1f, 0.1f, 0.1f);
	FVector Location;
	FRotator Rotation;

	//Default mesh and material
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoreMesh(TEXT("/Game/ProjectS/StaticMesh/SM_Core"));
	UStaticMesh* SM_Core = CoreMesh.Object;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMesh(TEXT("/Game/ProjectS/StaticMesh/SM_Arrow"));
	UStaticMesh* SM_Arrow = ArrowMesh.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> ArrowMaterial(TEXT("/Game/ProjectS/Material/MI_Arrow"));
	UMaterialInstance* MI_Arrow = ArrowMaterial.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultOpenMaterial(TEXT("/Game/ProjectS/Material/Red"));
	OpenMaterial = DefaultOpenMaterial.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder(TEXT("/Game/ProjectS/Data/DT_Star"));
	DataTable = DataTableFinder.Object;
	// GetDataTableRow
	// FStarsStruct* Item = DataTable->FindRow<FStarsStruct>(Name, "");	
	// GetDataTableRow
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultCloseMaterial(TEXT("/Game/ProjectS/Material/Blue"));
	CloseMaterial = DefaultCloseMaterial.Object;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	SceneComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));

	CentralObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CentralObject"));
	CentralObject->SetupAttachment(GetRootComponent());
	CentralObject->SetStaticMesh(SM_Core);
	CentralObject->SetMaterial(0, MI_Arrow);

	ArrowTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowTop"));
	Rotation = FRotator(0.0f ,180.0f ,0.0f);
	Location = FVector(0.0f, 100.0f, 0.0f);
	AllocateArrow(ArrowTop, SM_Arrow, MI_Arrow, Scale, Location, Rotation);

	ArrowRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowRight"));
	Rotation = FRotator(0.0f ,-90.0f ,0.0f);
	Location = FVector(-100.0f, 0.0f, 0.0f);
	AllocateArrow(ArrowRight, SM_Arrow, MI_Arrow, Scale, Location, Rotation);

	ArrowDown = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowDown"));
	Rotation = FRotator(0.0f ,0.0f ,0.0f);
	Location = FVector(0.0f, -100.0f, 0.0f);
	AllocateArrow(ArrowDown, SM_Arrow, MI_Arrow, Scale, Location, Rotation);
	
	ArrowLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowLeft"));
	Rotation = FRotator(0.0f ,90.0f ,0.0f);
	Location = FVector(100.0f, 0.0f, 0.0f);;
	AllocateArrow(ArrowLeft, SM_Arrow, MI_Arrow, Scale, Location, Rotation);

}

void ACPPSpaceObject::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ACPPMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MapBuilder = Cast<ACPPMapBuilder>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPPMapBuilder::StaticClass()));
	CentralObject->OnClicked.AddDynamic(this, &ACPPSpaceObject::OnStarClicked);
	if (!bDiscovered)
	{
		Draw();
	}
}

void ACPPSpaceObject::OnStarClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Error, TEXT("Test with %s"),*TouchedComponent->GetName());
	GameMode->MovePlayerToLocations(this);
}

void ACPPSpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time += DeltaTime;
	CalcObjectsPositionsOnOrbit();
	ReallocateObjectsOnOrbit();
}

void ACPPSpaceObject::OnDiscovered() const
{
	DrawArrows();
	CentralObject->SetMaterial(0, OpenMaterial);
}

void ACPPSpaceObject::SetProperties(FStarsStruct* Struct)
{
	/*FStarsStruct* StarStract = Cast<FStarsStruct>(Struct);*/
	Name = Struct->Name;
	Direction = Struct->Direction;
	OpenMaterial = Struct->Material;
}



void ACPPSpaceObject::AllocateArrow(UStaticMeshComponent* Arrow,
                                    UStaticMesh* Mesh,
                                    UMaterialInstance* Material,
                                    FVector Scale,
                                    FVector Location,
                                    FRotator Rotation) const
{
		Arrow->SetupAttachment(GetRootComponent());
		Arrow->SetStaticMesh(Mesh);
		Arrow->SetMaterial(0, Material);
		Arrow->SetRelativeScale3D(Scale);
		Arrow->SetRelativeLocation(Location);
		Arrow->SetRelativeRotation(Rotation);
		Arrow->SetVisibility(false);
}

FVector2d ACPPSpaceObject::GetCoords() const
{
	return FVector2d(PosX, PosY);
}

//int32 ACPPSpaceObject::GetGridStep() const
//{
//	return GridStep;
//}

void ACPPSpaceObject::EnableArrowTop() const
{
	ArrowTop->SetVisibility(true);
}

void ACPPSpaceObject::EnableArrowRight() const
{
	ArrowRight->SetVisibility(true);
}

void ACPPSpaceObject::EnableArrowDown() const
{
	ArrowDown->SetVisibility(true);
}

void ACPPSpaceObject::EnableArrowLeft() const
{
	ArrowLeft->SetVisibility(true);
}

void ACPPSpaceObject::DisableArrowTop() const
{
	ArrowTop->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowRight() const
{
	ArrowRight->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowDown() const
{
	ArrowDown->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowLeft() const
{
	ArrowLeft->SetVisibility(false);
}

void ACPPSpaceObject::DisableArrowAndDirection(int32 direction)
{
	switch (direction)
	{
	case 1:
		{
			DisableArrowTop();
			DisableDirection(direction);
			break;
		}
	case 2:
		{
			DisableArrowRight();
			DisableDirection(direction);
			break;
		}
	case 4:
		{
			DisableArrowDown();
			DisableDirection(direction);
			break;
		}
	case 8:
		{
			DisableArrowLeft();
			DisableDirection(direction);
			break;
		}
	}
}

void ACPPSpaceObject::EnableArrowAndDirection(int32 direction)
{
	switch (direction)
	{
	case 1:
		{
			EnableArrowTop();
			EnableDirection(direction);
			break;
		}
	case 2:
		{
			EnableArrowRight();
			EnableDirection(direction);
			break;
		}
	case 4:
		{
			EnableArrowDown();
			EnableDirection(direction);
			break;
		}
	case 8:
		{
			EnableArrowLeft();
			EnableDirection(direction);
			break;
		}
	}
}

bool ACPPSpaceObject::CanMoveTop() const
{
	return CalcDirection(1)== 1;
}

bool ACPPSpaceObject::CanMoveDown() const
{
	return CalcDirection(4)== 4;
}

bool ACPPSpaceObject::CanMoveRight() const
{
	return CalcDirection(2)== 2;
}

bool ACPPSpaceObject::CanMoveLeft() const
{
	return CalcDirection(8)== 8;
}

int32 ACPPSpaceObject::CalcDirection(int32 CalcDirection) const
{
	return  CalcDirection & Direction;
}

void ACPPSpaceObject::EnableDirection(int32 DirectionToEnable)
{
	Direction = DirectionToEnable | Direction;
}
void ACPPSpaceObject::DisableDirection(int32 DirectionToDisable)
{
	Direction = ~DirectionToDisable & Direction;
}

TArray<int32> ACPPSpaceObject::GetAllowDirectionList() const
{
	TArray<int32> DirectionList;
	if(CanMoveTop())
	{
		DirectionList.Add(1);
	}
	if(CanMoveRight())
	{
		DirectionList.Add(2);
	}
	if(CanMoveDown())
	{
		DirectionList.Add(4);
	}
	if(CanMoveLeft())
	{
		DirectionList.Add(8);
	}
	return DirectionList;
}

void ACPPSpaceObject::DrawArrows() const
{
	if(CanMoveTop())
	{
		EnableArrowTop();
	}
	if(CanMoveRight())
	{
		EnableArrowRight();
	}
	if(CanMoveDown())
	{
		EnableArrowDown();
	}
	if(CanMoveLeft())
	{
		EnableArrowLeft();
	}
}

void ACPPSpaceObject::Draw()
{
	auto LocationX = (PosX*GridStep);
	auto LocationY = (PosY*GridStep);
	const FVector NewLocation = FVector(LocationX, LocationY, 0.0f);
	SetActorLocation(NewLocation);
}

void ACPPSpaceObject::CalcObjectsPositionsOnOrbit()
{
	Positions.Empty();
	const auto &ContainerPosition = GetActorLocation();
	auto Step = PI * 2 / OrbitalObjects.Num();
	for (int i = 1; i <= OrbitalObjects.Num(); i++)
	{
		auto Angle = i * Step;
		auto Cos = UKismetMathLibrary::Cos(Angle + (OrbitalSpeed * Time));
		auto Sin = UKismetMathLibrary::Sin(Angle + (OrbitalSpeed * Time));
		auto XPos = Cos * OrbitalRadius;
		auto YPos = Sin * OrbitalRadius;
		FVector Position = FVector((ContainerPosition.X + XPos), (ContainerPosition.Y + YPos), 0.0f);
		Positions.Add(Position);
	}
}

void ACPPSpaceObject::AddSpaceObjectToOrbit(ACPPOrbitalObject* ObjectToAdd)
{
	OrbitalObjects.Add(ObjectToAdd);
}

void ACPPSpaceObject::ReallocateObjectsOnOrbit()
{
	for (int i = 0; i < OrbitalObjects.Num(); i++)
	{
		OrbitalObjects[i]->SetActorLocation(Positions[i]);
	}
}

void ACPPSpaceObject::RemoveObjectFromOrbit(ACPPOrbitalObject* ObjectToRemove)
{
	Positions.Remove(ObjectToRemove->GetActorLocation());
	OrbitalObjects.Remove(ObjectToRemove);
}

void ACPPSpaceObject::DiscoverStar()
{
	if (bDiscovered) return;
	if (!Name.IsNone()) return;
	MapBuilder->DiscoverStar(GetCoords());
	MapBuilder->CreateUndiscoveredStars(GetAllowDirectionList(), GetCoords());
	bDiscovered = true;
}
