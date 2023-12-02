// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/Crop.h"
#include "MainFarmCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"


AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bEnableClickEvents=true;
	
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	Locomotion();
	CursorTrace();
	//도착지가 있는경우 interp작동시키기
	if(target != nullptr)
	{
		FVector NewLocation = FMath::VInterpTo(mainFarmCharacter->GetActorLocation(),target->GetActorLocation(),DeltaTime,interpSpeed);
		mainFarmCharacter->SetActorLocation(NewLocation);
		
		float distance =FVector::Distance(mainFarmCharacter->GetActorLocation(),target->GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("Character Stamina :: %f"), distance);
		if(distance<=110)
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"distance<5");
			if(clickedCrop->myType==ECropProgressState::growState)
			{
			 growProgress();
			}
			if(clickedCrop->myType==ECropProgressState::growState)
			{
				cropProgress();
			}
			target=nullptr;
		}
	}
	
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

	mainFarmCharacter = Cast<AMainFarmCharacter>(GetCharacter());
	//controller입장에서 character찾기는 getowner 가 아니라 GetCharacter !!
	
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &AMainPlayerController::LookUp);
	EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &AMainPlayerController::Turn);
	EnhancedInputComponent->BindAction(ClickIA, ETriggerEvent::Started, this, &AMainPlayerController::Clicked);
	
}



void AMainPlayerController::Move(const FInputActionValue& Value)
{
	/*const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector forwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(forwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(rightDirection, InputAxisVector.X);
	}*/
	const FVector CurrentValue = Value.Get<FVector>();
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
    //방향을 초기화
    moveDir = FVector::ZeroVector;
}

void AMainPlayerController::LookUp(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddControllerPitchInput(_currentValue);		//
	}
	
}

void AMainPlayerController::Turn(const FInputActionValue& Value)
{
	const float _currentValue = Value.Get<float>();
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddControllerYawInput(_currentValue);		//
	}
	
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

void AMainPlayerController::Clicked()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	
	clickedCrop = Cast<ACrop>(HitResult.GetActor());
	if(clickedCrop)
	{
		if(clickedCrop->myType==ECropProgressState::growState)
		{
			if(mainFarmCharacter)
			{
			   GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"crop 0 state Clicked");
				target=clickedCrop;
				
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"mainFarmCharacter ==null");
			}
		}
		
		if(clickedCrop->myType==ECropProgressState::cropState)
		{
			target=clickedCrop;
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"ECropProgressState::cropState");
			
			//인벤토리에 넣기
		}
	}
	
	/*if (HitResult.GetComponent())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Component: %s"), *HitResult.GetComponent()->GetName()) );
	}

	if (HitResult.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));
	}*/
}

