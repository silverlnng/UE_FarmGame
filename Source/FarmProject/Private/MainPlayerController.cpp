// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/Crop.h"
#include "MainFarmCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bEnableClickEvents=true;
	
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//Locomotion();
	CursorTrace();
	//도착지가 있는경우 interp작동시키기
	
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
	EnhancedInputComponent->BindAction(ClickIA, ETriggerEvent::Started, this, &AMainPlayerController::Clicked);
	
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

void AMainPlayerController::Clicked()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	
	ACrop* crop = Cast<ACrop>(HitResult.GetActor());
	if(crop)
	{
		if(crop->myType==ECropProgressState::growState)
		{
			if(mainFarmCharacter)
			{
			 GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"crop 0 state Clicked");
			/*mainFarmCharacter->GetCharacterMovement()
			->MoveSmooth(crop->GetActorLocation().GetSafeNormal(),5);*/
				FVector temp = crop->GetActorLocation()-mainFarmCharacter->GetActorLocation();
				mainFarmCharacter->GetCharacterMovement()
				->MoveSmooth(temp,5);
				
				//플레이어의 농사 애니메이션 몽타주 작동시키기
				mainFarmCharacter->ChangedAnimMontage(1);
				//crop의 grow 타이머 작동시키기
				//
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"mainFarmCharacter ==null");
			}
		}
		
		if(crop->myType==ECropProgressState::cropState)
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"ECropProgressState::cropState");
			FVector temp = crop->GetActorLocation()-mainFarmCharacter->GetActorLocation();
			mainFarmCharacter->GetCharacterMovement()
			->MoveSmooth(temp,5);
			//mainFarmCharacter->GetCharacterMovement()->Move
			//플레이어의 수확 애니메이션 몽타주 작동시키기
			//ECropProgressState::growState 으로 변경시키기
			//인벤토리에 넣기
		}
	}
	
	if (HitResult.GetComponent())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Component: %s"), *HitResult.GetComponent()->GetName()) );
	}

	if (HitResult.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));
	}
}

