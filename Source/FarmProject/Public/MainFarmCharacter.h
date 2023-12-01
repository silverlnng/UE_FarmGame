// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "FarmCharacterBase.h"
#include "MainFarmCharacter.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;

UCLASS()
class FARMPROJECT_API AMainFarmCharacter : public AFarmCharacterBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
public:
	AMainFarmCharacter();
	
	virtual void PossessedBy(AController* NewController) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnyWhere, Category = "Camera")
	class UCameraComponent* CameraComp;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> hat;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> hair;

	UFUNCTION(BlueprintCallable)	
	void ChangedAnimMontage(int32 index);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "animation")
	TArray<UAnimMontage*> AnimMotageArray;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "animation")
	UAnimMontage
};
