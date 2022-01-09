// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	
	if (ShooterCharacter)
	{
		// Get the speed of the Character form velocity
		FVector Velocity{ ShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();			//캐릭터가 위쪽으로 날아가거나 아래로 떨어지는 경우 이 속도 변수에 영향을 안준다

		// Is the Character in the air?
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		//Is the Character accelerating?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}
		
		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;


		//FString RotationMessage = FString::Printf(TEXT("Base Aim Rotation : %f"), AimRotation.Yaw);
		//FString MovementRotationMessage = FString::Printf(TEXT("MovementRotation  : %f"), MovementRotation.Yaw);

		FString OffsetMessage = FString::Printf(TEXT("MovementOffsetYaw Rotation : %f"), MovementOffsetYaw);

		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, RotationMessage);
			//GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::White, MovementRotationMessage);
			GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::White, OffsetMessage);
		}

	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}