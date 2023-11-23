// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


AMainPlayerController::AMainPlayerController()
{
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(PlayerMappingContext);
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);
	subsystem->AddMappingContext(PlayerMappingContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	const FVector CurrentValue = Value.Get<FVector>();
	//CurrentValue �� x,y �� input ������ ���������� x,y �� �ƴ� 

	//moveDir.x y �� ��������. �׷��� CurrentValue�� ���� .
	moveDir.X = CurrentValue.Y;
	moveDir.Y = CurrentValue.X;
	
}

void AMainPlayerController::Locomotion()
{
	moveDir = FTransform(GetControlRotation()).TransformVector(moveDir);
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(moveDir);		//
	}
    //������ �ʱ�ȭ
    moveDir = FVector::ZeroVector;
}
