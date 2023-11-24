// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CustomDataTable.generated.h"

USTRUCT(BlueprintType)
struct FFarmDataRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 corn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 pumpkin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 lettuce;
};


UCLASS()
class FARMPROJECT_API ACustomDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomDataTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
