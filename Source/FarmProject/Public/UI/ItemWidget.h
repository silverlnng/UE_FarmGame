// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "ItemWidget.generated.h"

struct ItemstructDetail
{
	FName name;
	float cost;
	UTexture2D image;
};

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FName itemID;
	ItemstructDetail itemDetail;
	UPROPERTY(EditAnywhere)
	UDataTable* itemDataTable;
	void GetDataTableRowNames(FName rowID);
};
