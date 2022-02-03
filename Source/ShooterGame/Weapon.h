// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AmmoType.h"
#include "Engine/DataTable.h"
#include "WeaponType.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponDataTable : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAmmoType AmmoType;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 WewaponAmmo;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MagazingCapacity;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* PickupSound;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* EquipSound;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* ItemMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* InventoryIcon;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* AmmoIcon;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstance* MaterialInstance;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaterialIndex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ClipBoneName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ReloadMontageSection;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UAnimInstance> AnimBP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CrosshairsMiddle;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CrossHairLeft;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CrosshairsRight;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CrosshairsBottom;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CrosshairsTop;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AutoFireRate;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* MuzzleFlash;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* FireSound;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName BoneToHide;
};

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	AWeapon();

	virtual void Tick(float DletaTime) override;
protected:
	void StopFalling();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	void FinishMovingSlide();
	void UpdateSlideDisplacement();

private:
	FTimerHandle ThrowWeaponTimer;
	float ThrowWeaponTime;
	bool bFalling;

	/**Ammo count for this Weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties",meta = (AllowPrivateAccess = "true"))
	int32 Ammo;

	/**Maximum ammo that our weapon can hold*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties",meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;
	/**The Weapon Type*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties",meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	/** The type of ammo for this weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties",meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties",meta = (AllowPrivateAccess = "true"))
	FName ReloadMontageSection;

	/**Moving the clip while reloading*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	bool bMovingClip;
	/**Name Clip bone*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	FName ClipBoneName;

	/**Data Table Weapon Properties*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDataTable;

	int32 PreviousMaterialIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsMiddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrossHairLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsBottom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsTop;

	/** The speed at which automatic fire happens*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	float AutoFireRate;

	/** Particle System spawned at the BarrelSocket*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;

	/** Sound played when the weapon is Fire*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DataTable, meta = (AllowPrivateAccess = "true"))
	FName BoneToHide;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pistol, meta = (AllowPrivateAccess = "true"))
	float SlideDisplacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pistol, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* SlideDisplacementCurve;

	/**Timer Handle for udpating SlideDisplacemnet*/
	FTimerHandle SlideTimer;

	/**Time for displacing the slide during pistol fire*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pistol, meta = (AllowPrivateAccess = "true"))
	float SlideDisplacemnetTime;

	/** Ture when moving the pistol slide*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pistol, meta = (AllowPrivateAccess = "true"))
	bool bMovingSlide;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pistol, meta = (AllowPrivateAccess = "true"))
	float MaxSlideDisplacement;

public:
	void ThrowWeapon();
	FORCEINLINE int32 GetAmmo() const { return Ammo; }
	FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity; }
	
	

	/**Called from Charracter class when firing weapon*/
	void DecrementAmmo();

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }
	FORCEINLINE FName GetReloadMontageSection() const { return ReloadMontageSection; }
	void ReloadAmmo(int32 Amount);

	FORCEINLINE FName GetClipBoneName() const { return ClipBoneName; }
	void SetMovingClip(bool Move) { bMovingClip = Move; }
	
	FORCEINLINE  void SetClipBoneName(FName name) { ClipBoneName = name; }
	FORCEINLINE void SetReloadMontageSection(FName name) { ReloadMontageSection = name; }

	FORCEINLINE float GetAutoFireRate() const { return AutoFireRate; }
	FORCEINLINE UParticleSystem* GetMuzzleFlash() const { return MuzzleFlash; }
	FORCEINLINE USoundCue* GetFireSound() const { return FireSound; }

	bool ClipIsFull();

	void StartSlideTimer();
};
