// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UItemShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ANPC* ownerNPC;	
	
};
