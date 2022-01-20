// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EOffsetState : uint8
{
	EOS_Aiming			UMETA(DisplayName = "Aiming"),
	EOS_Hip					UMETA(DisplayName = "Hip"),
	EOS_Reloading		UMETA(DisplayName = "Reloading"),
	EOS_InAir				UMETA(DisplayName = "InAir"),

	EOS_MAX				UMETA(DisplayName = "DefaultMAX")
};

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UShooterAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;



protected:
	/** Handle Truning in place */
	void TurnInPlace();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class AShooterCharacter* ShooterCharacter;

	/**The speed of the Character*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =  Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	/** Whether or not the Character is in the air*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	/** Whether or not the Character is moving */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	/**offset yaw used for strafing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MovementOffsetYaw;

	/**Offset yaw the frame before we stopped moving*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float LastMovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bAiming;
	
	/** Yaw of the Character this frame*/
	float CharacterYaw;

	/** Yaw of the Character previous frame*/
	float CharacterYawLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place",meta = (AllowPrivateAccess = "true"))
	float RootYawOffset;

	/**Rotation Curve value this frame*/
	float RotationCurve;

	/** Rotation CurveValue last frame*/
	float RotationCurveLastFrame;

	/** The pitch of the aim rotation, used for aim offset */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place",meta = (AllowPrivateAccess = "true"))
	float Pitch;

	/**True when realoding used to prevent aim offset while reloading*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place",meta = (AllowPrivateAccess = "true"))
	bool bReloading;

	/**Offset State*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Turn In Place",meta = (AllowPrivateAccess = "true"))
	EOffsetState OffsetState;
};
