#include "Pawns/BasePawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetSimulatePhysics(true);
	BaseMesh->SetEnableGravity(true);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun mesh"));
	Gun->SetupAttachment(TurretMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Projectile"));
	ProjectileSpawnPoint->SetupAttachment(Gun);

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Effect"));
	Explosion->SetupAttachment(BaseMesh);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CoolDown > 0.f) {
		CoolDown -= DeltaTime;

		if (CoolDown < 0.f) {
			CoolDown = 0.f;
		}
	}
}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	FRotator CurrentRotationBase = BaseMesh->GetRelativeRotation();
	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Pitch = CurrentRotationBase.Pitch;
	LookAtRotation.Roll = CurrentRotationBase.Roll;

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			InterpSpeed));
}

void ABasePawn::RotateGunAI(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - Gun->GetComponentLocation();

	FRotator CurrentRotation = Gun->GetRelativeRotation();

	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Pitch = FMath::Clamp(LookAtRotation.Pitch, MinPitch, MaxPitch);
	LookAtRotation.Yaw = CurrentRotation.Yaw;
	LookAtRotation.Roll = CurrentRotation.Roll;

	Gun->SetRelativeRotation(
		FMath::RInterpTo(
			CurrentRotation,
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			InterpSpeed));
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();
	FVector Scale = ProjectileScale;
	FTransform SpawnProjectileTransform(ProjectileSpawnPointRotation, ProjectileSpawnPointLocation, Scale);

	if (ProjectileClass != nullptr)
	{
		if (CoolDown <= 0.f) {
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnProjectileTransform);
			Projectile->SetOwner(this);
			CoolDown = Base_CD;

			if (FireSFX)
			{
				UGameplayStatics::PlaySoundAtLocation(
					this,
					FireSFX,
					GetActorLocation());
			}
		}
	}	
}
