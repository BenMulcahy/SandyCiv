// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/ObjectLibrary.h"
#include "GameFramework/Actor.h"
#include "Container.generated.h"

UCLASS()
class SANDYCIV_API AContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainer();

	virtual void OnConstruction(const FTransform& Transform) override;


protected:

	
	/// <summary>
	/// Select Random Mesh for each section
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetRandomMeshes();

	UFUNCTION(BlueprintCallable)
	void SetChosenMesh(UStaticMeshComponent* panelMesh,UObjectLibrary* meshlibrary ,int meshIndex);

	/// <summary>
	/// Get mesh from given object library asset at random or given index
	/// </summary>
	TObjectPtr<UStaticMesh> ChooseMeshFromObjLibrary(UObjectLibrary* meshLibrary, bool bRandomMesh = true ,int meshIndex = 0.f);

	FORCEINLINE UFUNCTION()
	TObjectPtr<UStaticMesh> GetMeshFromFilePath(FString filePath)
	{
		return Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *filePath));
	}

private:
	/// <summary>
	/// Helper function for setting mesh on given component
	/// </summary>
	bool SetPanelStaticMesh(TObjectPtr<UStaticMeshComponent> meshComponent, TObjectPtr<UStaticMesh> newMesh);

#pragma region Properties

public:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UObjectLibrary> doorsLibrary_L = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UObjectLibrary> doorsLibrary_R = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UObjectLibrary> wallsLibrary = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UObjectLibrary> roofLibrary = nullptr;


	UPROPERTY(EditAnywhere, DisplayName = "DefaultSceneRoot")
	TObjectPtr<USceneComponent> m_root;

	UPROPERTY(BlueprintReadOnly, Category = "Floor", DisplayName = "Container Floor")
	TObjectPtr<UStaticMeshComponent> m_Container_Floor;

	UPROPERTY(BlueprintReadOnly, Category = "Roof", DisplayName = "Container Roof")
	TObjectPtr<UStaticMeshComponent> m_Container_Roof;

#pragma region Walls

	UPROPERTY(BlueprintReadOnly, Category = "Walls", DisplayName = "Left Wall")
	TObjectPtr<UStaticMeshComponent> m_Wall_L;

	UPROPERTY(BlueprintReadOnly, Category = "Walls", DisplayName = "Right Wall")
	TObjectPtr<UStaticMeshComponent> m_Wall_R;

#pragma endregion

#pragma region Doors

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,Category = "Doors", meta=(EditInlineConditionToggle)) //TODO: EditInlineConditionToggle not functioning?
	bool bFrontAngleMatched = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Doors", meta=(Units = "Degrees", ClampMin = 0, ClampMax = 240, UIMin = 0, UIMax = 240))
	float Door_Front_L_Angle;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Doors", meta = (EditCondition = "bFrontAngleMatched == false", EditConditionHides, Units = "Degrees", ClampMin = 0, ClampMax = 240, UIMin = 0, UIMax = 240)) 
	float Door_Front_R_Angle;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Doors", meta = (EditInlineConditionToggle))
	bool bRearAngleMatched = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Doors", meta = (Units = "Degrees", ClampMin = 0, ClampMax = 240, UIMin = 0, UIMax = 240))
	float Door_Rear_L_Angle;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Doors", meta = (EditCondition = "bRearAngleMatched == false", EditConditionHides, Units = "Degrees", ClampMin = 0, ClampMax = 240, UIMin = 0, UIMax = 240))
	float Door_Rear_R_Angle;

	UPROPERTY(BlueprintReadOnly, Category = "Doors", DisplayName = "Front Left Door")
	TObjectPtr<UStaticMeshComponent> m_Door_Front_L;

	UPROPERTY(BlueprintReadOnly, Category = "Doors", DisplayName = "Front Right Door")
	TObjectPtr<UStaticMeshComponent> m_Door_Front_R;

	UPROPERTY(BlueprintReadOnly, Category = "Doors", DisplayName = "Rear Left Door")
	TObjectPtr<UStaticMeshComponent> m_Door_Rear_L;

	UPROPERTY(BlueprintReadOnly, Category = "Doors", DisplayName = "Rear Right Door")
	TObjectPtr<UStaticMeshComponent> m_Door_Rear_R;

#pragma endregion

	UPROPERTY(VisibleDefaultsOnly, DisplayName = "Forward Arrow")
	TObjectPtr<UArrowComponent> m_arrowComponent;

#pragma endregion
};
