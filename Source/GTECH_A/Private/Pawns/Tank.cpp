#include "Pawns/Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	BaseMesh->SetMassOverrideInKg(NAME_None, 60000.f, true);
	BaseMesh->SetLinearDamping(2.0f);
	BaseMesh->SetAngularDamping(1.0f);

	Truck = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Truck mesh"));
	Truck->SetupAttachment(BaseMesh);

	L_truck = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_truck mesh"));
	L_truck->SetupAttachment(BaseMesh);

	R_truck = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_truck mesh"));
	R_truck->SetupAttachment(BaseMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BaseMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Camera_Turret = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera_Turret"));
	Camera_Turret->SetupAttachment(Gun);

	FVector LocalPivotOffset(100.f, 0.f, 100.f);
	Gun->SetRelativeLocation(LocalPivotOffset);

	for (int i = 0; i < 14; i++)
	{
		FString WheelName = FString::Printf(TEXT("Wheel%d"), i);
		UStaticMeshComponent* NewWheel = CreateDefaultSubobject<UStaticMeshComponent>(*WheelName);

		if (i < 7)
		{
			NewWheel->SetupAttachment(L_truck);
		}
		else
		{
			NewWheel->SetupAttachment(R_truck);
		}

		Wheels.Add(NewWheel);
	}

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	Camera_Turret->SetActive(false);
	TankPlayerController = Cast<APlayerController>(GetController());
	ShowReload();

	if (TankPlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
		}
	}
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECC_Visibility,
			false,
			HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATank::Move);
		}
		if (FireAction) {
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::Fire);
		}
		if (AimAction) {
			EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ATank::Aim);
		}
		if (AimZoomAction) {
			EnhancedInputComponent->BindAction(AimZoomAction, ETriggerEvent::Triggered, this, &ATank::AdjustFOV);
		}
		if (RotateGunUpAction) {
			EnhancedInputComponent->BindAction(RotateGunUpAction, ETriggerEvent::Triggered, this, &ATank::RotateGunUp);
		}
		if (RotateGunDownAction) {
			EnhancedInputComponent->BindAction(RotateGunDownAction, ETriggerEvent::Triggered, this, &ATank::RotateGunDown);
		}
	}	
}

void ATank::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller && L_truck && R_truck)
	{
		FVector ForceDirection = GetActorForwardVector() * MovementVector.Y * Speed;
		L_truck->AddForce(ForceDirection, NAME_None, true);
		R_truck->AddForce(ForceDirection, NAME_None, true);

		FVector Torque = FVector(0.f, 0.f, MovementVector.X * TurnRate);
		L_truck->AddTorqueInDegrees(Torque, NAME_None, true);
		R_truck->AddTorqueInDegrees(Torque, NAME_None, true);
	}
}


void ATank::Aim()
{
	Is_aiming = !Is_aiming;

	if (Is_aiming)
	{
		Camera->SetActive(false);
		Camera_Turret->SetActive(true);
		ActivateAim();
	}

	if (!Is_aiming)
	{
		Camera_Turret->SetActive(false);
		Camera->SetActive(true);
		DeactivateAim();
	}
}

void ATank::AdjustFOV(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	if (FMath::IsNearlyZero(AxisValue)) return;

	float NewFOV = FMath::Clamp(Camera_Turret->FieldOfView + (AxisValue * ZoomSpeed), MinFOV, MaxFOV);
	Camera_Turret->SetFieldOfView(NewFOV);
}

void ATank::RotateGunUp()
{
	FRotator CurrentRotation = Gun->GetRelativeRotation();
	CurrentGunPitch = FMath::Clamp(CurrentGunPitch + InterpSpeed, MinPitch, MaxPitch);
	FRotator LookAtRotation = FRotator(CurrentGunPitch, CurrentRotation.Yaw, CurrentRotation.Roll);

	Gun->SetRelativeRotation(
	FMath::RInterpTo(
		CurrentRotation,
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		InterpSpeed));
}

void ATank::RotateGunDown()
{
	FRotator CurrentRotation = Gun->GetRelativeRotation();
	CurrentGunPitch = FMath::Clamp(CurrentGunPitch - InterpSpeed, MinPitch, MaxPitch);
	FRotator LookAtRotation = FRotator(CurrentGunPitch, CurrentRotation.Yaw, CurrentRotation.Roll);

	Gun->SetRelativeRotation(
		FMath::RInterpTo(
			CurrentRotation,
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			InterpSpeed));
}


float ATank::GetCoolDown() const
{
	return this->CoolDown;
}

float ATank::GetBase_CD() const
{
	return this->Base_CD;
}

void ATank::SetCamera(bool Active)
{
	if (Camera)
	{
		Camera->SetActive(Active);
	}
}

void ATank::SetCamera_Turret(bool Active)
{
	if (Camera_Turret)
	{
		Camera_Turret->SetActive(Active);
	}
}