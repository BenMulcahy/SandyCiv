// Fill out your copyright notice in the Description page of Project Settings.


#include "Container.h"

// Sets default values
AContainer::AContainer()
{
	PrimaryActorTick.bCanEverTick = false;

#pragma region SetupDefaultObjects

	m_root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = m_root;
	
	m_arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	m_arrowComponent->SetupAttachment(RootComponent);
	m_arrowComponent->SetRelativeLocation(FVector(285, 0, 90));
	m_arrowComponent->SetArrowSize(1.15);

	m_Door_Front_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front_Door_L"));
	
	m_Door_Front_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front_Door_R"));
	m_Door_Rear_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear_Door_L"));
	m_Door_Rear_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear_Door_R"));

	m_Door_Front_L->SetupAttachment(RootComponent);
	m_Door_Front_R->SetupAttachment(RootComponent);
	m_Door_Rear_L->SetupAttachment(RootComponent);
	m_Door_Rear_R->SetupAttachment(RootComponent);

	m_Container_Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Container_Floor"));
	m_Container_Roof = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Container_Roof"));
	m_Container_Floor->SetupAttachment(RootComponent);
	m_Container_Roof->SetupAttachment(RootComponent);

	m_Wall_L = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Container_Wall_Left"));
	m_Wall_R = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Container_Wall_Right"));
	m_Wall_L->SetupAttachment(RootComponent);
	m_Wall_R->SetupAttachment(RootComponent);

	m_Container_Roof->SetRelativeLocation(FVector(0, 0, 255));
	m_Wall_L->SetRelativeLocation(FVector(0, 125.6, 13));
	m_Wall_R->SetRelativeLocation(FVector(0, -125.6, 13));
	m_Door_Front_L->SetRelativeLocation(FVector(316.433838, 125, 132.9));
	m_Door_Front_R->SetRelativeLocation(FVector(316.433838, -125, 132.9));
	m_Door_Rear_L->SetRelativeLocation(FVector(-316.433838, -125, 132.9));
	m_Door_Rear_R->SetRelativeLocation(FVector(-316.433838, 125, 132.9));

	bFrontAngleMatched = true;
	bRearAngleMatched = true;
#pragma endregion

}

void AContainer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	/// SET DOORS ANGLES ///
	if (bFrontAngleMatched)
	{
		m_Door_Front_L->SetRelativeRotation(FRotator(0, Door_Front_L_Angle,0).Quaternion());
		m_Door_Front_R->SetRelativeRotation(FRotator(0.f, Door_Front_L_Angle * -1,0).Quaternion());
	}
	else
	{
		m_Door_Front_L->SetRelativeRotation(FRotator(0, Door_Front_L_Angle, 0).Quaternion());
		m_Door_Front_R->SetRelativeRotation(FRotator(0.f, Door_Front_R_Angle *-1, 0).Quaternion());
	}

	if (bRearAngleMatched)
	{
		m_Door_Rear_L->SetRelativeRotation(FRotator(0, Door_Rear_L_Angle + 180, 0).Quaternion());
		m_Door_Rear_R->SetRelativeRotation(FRotator(0.f, (Door_Rear_L_Angle * -1) + 180, 0).Quaternion());
	}
	else
	{
		m_Door_Rear_L->SetRelativeRotation(FRotator(0, Door_Rear_L_Angle + 180, 0).Quaternion());
		m_Door_Rear_R->SetRelativeRotation(FRotator(0.f, (Door_Rear_R_Angle * -1) + 180, 0).Quaternion());
	}
}


bool AContainer::SetPanelStaticMesh(TObjectPtr<UStaticMeshComponent> meshComponent, TObjectPtr<UStaticMesh> newMesh)
{
	meshComponent->SetStaticMesh(newMesh);

	if (meshComponent->GetStaticMesh() == newMesh) return true;
	else return false;
}


TObjectPtr<UStaticMesh> AContainer::ChooseMeshFromObjLibrary(UObjectLibrary* meshLibrary, bool bRandomMesh, int meshIndex)
{
	if (!IsValid(meshLibrary)) return nullptr;

	TObjectPtr<UStaticMesh> mesh;
	TArray<UObject*> libArray;
	meshLibrary->GetObjects(libArray); //get all objects from obj library and out to libArray

	//Get mesh index either random or passed index
	float i = 0;
	if (bRandomMesh)
	{
		i = FMath::RandRange(0, libArray.Num() - 1);
	}
	else i = meshIndex;

	//Get object at given index
	TObjectPtr<UObject> libAsset = libArray[i];
	if (IsValid(libAsset) && libAsset.GetClass() == UStaticMesh::StaticClass()) //check object is mesh
	{
		mesh = (UStaticMesh*)libAsset;
		return mesh; //return mesh pointer
	}
	else return nullptr;
}

//Set random mesh on each component
void AContainer::SetRandomMeshes()
{
	m_Wall_L->SetStaticMesh(ChooseMeshFromObjLibrary(wallsLibrary));
	m_Wall_R->SetStaticMesh(ChooseMeshFromObjLibrary(wallsLibrary));
	m_Container_Roof->SetStaticMesh(ChooseMeshFromObjLibrary(roofLibrary));
	m_Door_Front_L->SetStaticMesh(ChooseMeshFromObjLibrary(doorsLibrary_L));
	m_Door_Front_R->SetStaticMesh(ChooseMeshFromObjLibrary(doorsLibrary_R));
	m_Door_Rear_L->SetStaticMesh(ChooseMeshFromObjLibrary(doorsLibrary_L));
	m_Door_Rear_R->SetStaticMesh(ChooseMeshFromObjLibrary(doorsLibrary_R));
}

//set mesh on given component with given index
void AContainer::SetChosenMesh(UStaticMeshComponent* panelMesh, UObjectLibrary* meshLibrary, int meshIndex)
{
	if (panelMesh != nullptr)
	{
		meshIndex = FMath::Clamp(meshIndex, 0, meshLibrary->GetObjectCount() -1); //clamp index to mesh library
		panelMesh->SetStaticMesh(ChooseMeshFromObjLibrary(meshLibrary, false, meshIndex));
	}
}






