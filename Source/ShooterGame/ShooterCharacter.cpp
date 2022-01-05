// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay() called"));

	int MyInt{ 42 };
	UE_LOG(LogTemp, Warning, TEXT("int myInt: %d"), MyInt);

	float myFloat{ 3.14159f };	//f를 포함하지않으면 이중 리터럴 값이 축소변환을 이르킨다. 
	UE_LOG(LogTemp, Warning, TEXT("float myFloat: %f"), myFloat);

	double myDouble{ 0.000756 };
	UE_LOG(LogTemp, Warning, TEXT("double myDouble: %lf"), myDouble);

	char myChar{ 'J' };
	UE_LOG(LogTemp, Warning, TEXT("char myChar: %c"), myChar);

	wchar_t wideChar{ L'J' };
	UE_LOG(LogTemp, Warning, TEXT("wchar_t wideChar: %lc"), wideChar);

	bool myBool{ true };
	UE_LOG(LogTemp, Warning, TEXT("bool myBool: %d"), myBool);

	
	UE_LOG(LogTemp, Warning, TEXT("int : %d, float : %f, bool: %d"), MyInt, myFloat, myBool);

	FString myString{ TEXT("My String!!!") };
	UE_LOG(LogTemp, Warning, TEXT("FString myString: %s"), *myString);

	UE_LOG(LogTemp, Warning, TEXT("Name of Instance: %s"), *GetName());

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

