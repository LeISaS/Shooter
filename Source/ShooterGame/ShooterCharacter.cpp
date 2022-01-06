// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a camera boom (pulls in toward the Character if there is a cllision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);	//플레이어 따라가게 붙이기
	CameraBoom->TargetArmLength = 300.f;					//플레이어와 카메라와의 거리
	CameraBoom->bUsePawnControlRotation = true;		//컨트롤러가 이동할 때마다 카메라 회전사용 - Rotate the arm basesed on the controller

	//Create a follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);	//Attach caemra to end of boom
	FollowCamera->bUsePawnControlRotation = false; //Camera does not rotate relative to arm


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();




}

void AShooterCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw,0 };

		//컨트롤러 방향을 가리키고있다.
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };	//회전행렬에서 X축을 얻고 우리는 회전을 사용한다.
		AddMovementInput(Direction, Value);

	}

}

void AShooterCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw,0 };

		//컨트롤러 방향을 가리키고있다.
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };	//회전행렬에서 X축을 얻고 우리는 회전을 사용한다.
		AddMovementInput(Direction, Value);

	}
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

	//플레이어 입력 구성 요소가 유효하지 않은 경우 실행을 중지함
	check(PlayerInputComponent);


	//축매핑
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);


}

