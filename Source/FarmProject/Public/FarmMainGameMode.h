// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AFarmMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	AFarmMainGameMode();
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UMainUserWidget> mainWidgetClass;
	
	UPROPERTY()
	UMainUserWidget* mainWidget;

	UPROPERTY(EditAnywhere, Category = "Time")
	int32 currentTime;
	UPROPERTY(EditAnywhere, Category = "Time")
	int32 initTime;
	
};
