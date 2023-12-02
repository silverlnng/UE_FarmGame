// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Item/Crop.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class FARMPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveIA;		//UInputAction 사용은 헤더추가 , 클래스 전방선언 둘다 하기 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ClickIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMainFarmCharacter* mainFarmCharacter;
	
	UPROPERTY(EditAnywhere, Category = Speed)
	float interpSpeed;
	
	UFUNCTION(BlueprintImplementableEvent)
	void growProgress();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACrop* clickedCrop;
	UFUNCTION(BlueprintImplementableEvent)
	void cropProgress();
	
	
private:

	void Move(const FInputActionValue& Value);
	void Locomotion();
	FVector moveDir;
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	
	
	void CursorTrace();
	ACrop* LastActor;
	ACrop* ThisActor;
	
	void Clicked();
	AActor* target;
	int AnimMontage;
	
};
