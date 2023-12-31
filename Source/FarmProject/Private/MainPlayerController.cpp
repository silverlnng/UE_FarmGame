// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/Crop.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//Locomotion();
	CursorTrace();
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

	FInputModeGameAndUI InputModeData;

	//FInputModeGameAndUI : 입력 모드도 설정할 수 있습니다.
	/*이제 입력 모드 게임과 UI 구조체는 입력 모드 구조체이며, 이 입력 모드를 사용한다면
	키보드와 마우스의 입력을 사용할 수 있으며 입력을 사용하여 위젯과 같은 UI에 영향을 줄 수 있습니다.*/

	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector forwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(forwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(rightDirection, InputAxisVector.X);
	}
	
}

void AMainPlayerController::Locomotion()
{
	moveDir = FTransform(GetControlRotation()).TransformVector(moveDir);
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(moveDir);		//
	}
    //방향을 초기화
    moveDir = FVector::ZeroVector;
}

void AMainPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;
	//sGEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange, CursorHit.GetActor()->GetName());
	LastActor = ThisActor;
	ThisActor = Cast<ACrop>(CursorHit.GetActor());
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"this !=null");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"this,last both null");
			// Case A - both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
}

