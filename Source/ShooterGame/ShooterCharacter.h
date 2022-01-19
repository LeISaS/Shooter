// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	EAT_9mm			UMETA(DisplayName = "9mm"),
	EAT_AR			UMETA(DisplayName = "Assault Rifle"),

	EAT_MAX			UMETA(DisplayName = "Default Max")
};

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_Unoccupied					UMETA(DisplayName = "Unoccupied"),
	ECS_FireTimerInProgress		UMETA(DisplayName = "FireTimerInProgress"),
	ECS_Reloading						UMETA(DisplayName = "Reloading	"),

	ECS_Max								UMETA(DisplayName = "Default Max	")
};

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

	/**Rotate controller based on mouse X movement*/
	void Turn(float Value);

	/**Rotate controller based on mouse Y movement*/
	void LookUp(float Value);

	/**Fire Button Press*/
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	/**Set bAiming to true or false with button press*/
	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraInterpZoom(float DeltaTime);

	/** Set BaseTurnRate and BaseLookUpRate based on aiming*/
	void SetLookRates();

	void CalculateCrosshairSpread(float DeltaTime);

	void StartCrosshairBulletFire();

	UFUNCTION()
	void FinishCrosshairBulletFire();

	void FireButtonPressed();
	void FireButtonReleased();

	void StartFireTimer();
	UFUNCTION()
	void AutoFireReset();

	/**Line trace for items under ther crosshair*/
	bool TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation);

	/** Trace for items if OverlappedItemCount > 0*/
	void TraceForItems();

	/**Spawns a default weapon and equips it*/
	class AWeapon* SpawnDefaultWeapon();

	/**Takes a weapon and attaches it to the mesh*/
	void EquipWeapon(AWeapon* WeaponToEquip);

	/**Detach weapon and let it fall to the ground*/
	void DropWeapon();

	void SelectButtonPressed();
	void SelectButtonReleased();

	/**Drops currently equipped Weapon and Equips TraceHitItem*/
	void SwapWeapon(AWeapon* WeaponToSwap);

	/**InitializeAmmoMap */
	void InitializeAmmoMap();

	/**Check make sure our weapon was ammo*/
	bool WeaponHasAmmo();

	/**FireWeapon Functions*/
	void PlayFireSound();
	void SendBullet();
	void PlayGunFireMontage();
	/**Bound to the R key and Gamepad Face Button Left*/
	void ReloadButtonPressed();

	/**Handle Reloading of the weapon*/
	void ReloadWeapon();


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

	/** Trun rate while not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;

	/** Look up Rate when not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;

	/** Turn Rate when aiming */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;

	/**Look up rate when aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;
	
	/**Scale factor for mouse look sensitivity. Turn rate when not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0",ClampMax = "1.0",UIMin = "0.0",UIMax = "1.0"))
	float MouseHipTurnRate;

	/**Scale factor for mouse look sensitivity. Look up rate when not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;

	/**Scale factor for mouse look sensitivity. Turn rate when not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;

	/**Scale factor for mouse look sensitivity. Look up rate when not aiming*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;


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

	/** Current Field of view this frame*/
	float CameraCurrentFOV;

	/**Interp speed for zooming when aiming */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Combat, meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

	/** Determines the spread of the crosshairs */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairSpreadMultiplier;

	/**Velocity component for crosshairs spread*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairVelocityFactor;

	/**In air component for crosshairs spread*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairInAirFactor;

	/** Aim component for crosshairs spread*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairAimFactor;

	/** Shooting component for crosshairs spread*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairShootingFactor;

	float ShootTimeDuration;
	bool bFiringBullet;
	FTimerHandle CrosshairShootTimer;

	/** Left mouse button or right console trigger pressed */
	bool bFireButtonPressed;

	/** True when we can fire, false when waiting for the timer*/
	bool bShouldFire;

	/** Rate of automatic gun fire */
	float  AutomaticFireRate;

	/** Sets a timer between gunshots */
	FTimerHandle AutoFireTimer;

	/**True if we should trace every frame for items*/
	bool bShouldTraceForItems;

	/** Number of overlaped Aitems*/
	int8 OverlappedItemCount;

	/**The AItem we hit last frame*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = items, meta = (AllowPrivateAccess = "true"))
	class AItem* TraceHitItemLastFrame;

	/** Currently equipped Weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	/**Set this in Blueprints for default Weapon class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "ture"))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	/**Item currently hit by our trace in traceForItem*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "ture"))
	AItem* TraceHitItem;

	/**Distance outward from the camera for the interp destination*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	float CameraInterpDistance;

	/**Distance upward from the camera for the interp Desination*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	float CameraInterpElevation;

	/**Map ammo types*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int32> AmmoMap;

	/**Starting amount of 9mm ammo*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Items, meta = (AllowPrivateAccess = "true"))
	int32 Starting9mmAmmo;

	/**Starting amount of AR ammo*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Items, meta = (AllowPrivateAccess = "true"))
	int32 StartingARAmmo;

	/**CombatState can only fire or reload if unoccupied*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECombatState CombatState;

	/**Montage Reload Anim*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadMontage;

	UFUNCTION(BlueprintCallable)
	void FinishReloading();


public:
	
	/** Retruns CameraBoom Subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/**Retruns FollowCamera subobject*/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const;

	FORCEINLINE int8 GetOverlappedItemCount() const { return OverlappedItemCount; }

	/** Adds/Subtracts to/ from OverlappedItemCount and updates b Should TracforItems*/
	void IncrementOverlappedItemCount(int8 Amount);

	FVector GetCameraInterpLocation();

	void GetPickupItem(AItem* Item);
};
