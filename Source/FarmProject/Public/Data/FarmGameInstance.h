// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "FarmGameInstance.generated.h"

/*USTRUCT(BlueprintType)
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
};*/

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFarmGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
