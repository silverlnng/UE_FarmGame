// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetClockText(float num);
private:	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* clockText;
	
	UPROPERTY(meta = (BindWidget))
    UTextBlock* cropText;
	
};
