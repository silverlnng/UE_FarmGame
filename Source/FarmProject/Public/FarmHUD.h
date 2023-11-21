// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FarmHUD.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AFarmHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual  void BeginPlay() override;
private:	
	UPROPERTY(EditDefaultsOnly, Category = Slash)
	TSubclassOf<class UMainUserWidget> MainUserWidgetClass;

	UPROPERTY()
	UMainUserWidget* mainUserWidget;	

public:
	FORCEINLINE UMainUserWidget* GetMainUserWidget() const {return  mainUserWidget; }		
};
