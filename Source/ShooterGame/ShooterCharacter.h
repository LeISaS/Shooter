// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTERGAME_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backwards input*/
	void MoveForward(float Value);

	/**Called for side to side input*/
	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	/**Fire Button Press*/
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	/**Set bAiming to true or false with button press*/
	void AimingButtonPressed();
	void AimingButtonReleased();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	
	/**	 Caemra boom Positioning the caemra behind the character	*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Camera,meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Camera that follows the Character*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Camera,meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/**Base turn rate*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;
	
	/**Base lokk up/down rate*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	/**Randomized gunshot sound cue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;
	
	/**Flash spawned at BarrelSocket*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;

	/**Montage for Fire Weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	/**Particle Spawn Bullets*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	/**SmokeTrail for bullets*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticle;

	/**True when Aiming*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	/**Default camera field of view value */
	float CameraDefaultFOV;

	/**Field of View value for when zoomin*/
	float CameraZoomedFOV;

public:
	
	/** Retruns CameraBoom Subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/**Retruns FollowCamera subobject*/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
