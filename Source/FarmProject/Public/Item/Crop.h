// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Crop.generated.h"

/**
 * 
 */
UENUM(BlueprintType)	//언리얼 에디터에서 사용가능한 enum 선언
enum class ECropProgressState : uint8	//uint8형태만 있음 
{
	//DisplayName 안에 있는 내용으로 에디터에서 표시
	seedState UMETA(DisplayName = "seedState"),
	growState UMETA(DisplayName = "growState"),
	cropState UMETA(DisplayName = "cropState")
};  
UENUM(BlueprintType)	//언리얼 에디터에서 사용가능한 enum 선언
enum class ECropType : uint8	//uint8형태만 있음 
{
	//DisplayName 안에 있는 내용으로 에디터에서 표시
	corn UMETA(DisplayName = "corn"),
	pumpkin UMETA(DisplayName = "pumpkin"),
	wheat UMETA(DisplayName = "wheat"),
	lettuce UMETA(DisplayName = "lettuce")
};  
UCLASS()
class FARMPROJECT_API ACrop : public AItem
{
	GENERATED_BODY()
public:
	ACrop();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	
	
public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=CropType)
	ECropProgressState myType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere,Category=CropType)
	TArray<UStaticMesh*> cropMeshArray;

	UPROPERTY(EditAnywhere,Category=CropType)
	UCurveFloat* TimelineCurve;
	
	//타이머 세팅
	UPROPERTY(EditAnywhere,Category=CropTimer)
	float growingRate;
	
	UPROPERTY(EditAnywhere,Category=CropTimer)
	float firstDelay=2;
	
	UPROPERTY(EditAnywhere,Category=CropTimer)
	int32 RepeatingCallsMax = 3;
	
	UPROPERTY(EditAnywhere,Category=CropTimer)
	int32 RepeatingCalls = 0;
	
	FTimerHandle growingTimer;  
	void RepeatingGrowingFunction();
	UFUNCTION(BlueprintCallable)
	void StartTimer();
	
	void HighlightActor();
	void UnHighlightActor();
	
	UFUNCTION(BlueprintImplementableEvent)
	void growingSizeEffect();
};
