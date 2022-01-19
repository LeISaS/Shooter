// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AmmoType.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_SubmachineGun UMETA(DisplayName = "SubmachineGun"),
	EWT_AssaultRifle UMETA(DisplayName = "AssaultRifle"),

	EWT_MAX UMETA(DisplayName = "DefaultMax")
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
};
