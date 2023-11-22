// Fill out your copyright notice in the Description page of Project Settings.


#include "MainFarmCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void AMainFarmCharacter::BeginPlay()
{
	Super::BeginPlay();
}

AMainFarmCharacter::AMainFarmCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;
	springArmComp->bUsePawnControlRotation = true; //springArm은PawnControl을 따라가겠다 = Pawn을 축처럼 회전하게됨 

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(springArmComp);
	CameraComp->bUsePawnControlRotation = false; 

	bUseControllerRotationYaw = true;  //pwan에 이미 할당되어있는 컴포넌트여서 바로 접근할수있음 
}

void AMainFarmCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMainFarmCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainFarmCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
