// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Crop.generated.h"

/**
 * 
 */
UENUM(BlueprintType)	//언리얼 에디터에서 사용가능한 enum 선언
enum class ECropType : uint8	//uint8형태만 있음 
{
	//DisplayName 안에 있는 내용으로 에디터에서 표시
	cropBP_0 UMETA(DisplayName = "apple"),
	cropBP_1 UMETA(DisplayName = "Melon")
};  

UCLASS()
class FARMPROJECT_API ACrop : public AItem
{
	GENERATED_BODY()
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere)
	ECropType myType; 
	
};
