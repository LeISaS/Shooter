// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

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

public:
	void ThrowWeapon();
	FORCEINLINE int32 GetAmmo() const { return Ammo; }
	
	/**Called from Charracter class when firing weapon*/
	void DecrementAmmo();
};
