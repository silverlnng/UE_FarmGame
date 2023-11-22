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
	UPROPERTY(VisibleAnywhere,Category = "Widget")
	UMainUserWidget* mainWidget;
	
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class AFarmHUD> FarmHUD_BP;
	AFarmHUD* FarmHUD;
	
	UPROPERTY(EditAnywhere, Category = "Time")
	float currentTime = 0;
	UPROPERTY(EditAnywhere, Category = "Time")
	int32 initTime = 0;
	
};
