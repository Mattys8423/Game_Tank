#include "Projectiles/Projectile.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement component"));
	ProjectileMovementComponent->MaxSpeed = 2000.f;
	ProjectileMovementComponent->InitialSpeed = 2000.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpuse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();

	if (MyOwner == nullptr) return;

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if(ExplosionVFX)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				ExplosionVFX,
				GetActorLocation(),
				GetActorRotation());
		}

		ProjectileMesh->SetVisibility(false);
		ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

		GetWorldTimerManager().SetTimer(DelayBeforeDestroy, this, &AProjectile::DestroyProjectile, DelayDestroy, false);

	}
	else {
		ProjectileMesh->SetVisibility(false);
		ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetWorldTimerManager().SetTimer(DelayBeforeDestroy, this, &AProjectile::DestroyProjectile, DelayDestroy, false);
	}
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}


