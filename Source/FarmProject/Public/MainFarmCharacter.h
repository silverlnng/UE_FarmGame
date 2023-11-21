// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FarmCharacterBase.h"
#include "MainFarmCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AMainFarmCharacter : public AFarmCharacterBase
{
	GENERATED_BODY()
public:
	AMainFarmCharacter();
	virtual void PossessedBy(AController* NewController) override;

	
};
