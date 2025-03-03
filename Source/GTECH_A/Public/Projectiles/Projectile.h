#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class GTECH_A_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	void DestroyProjectile();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	UNiagaraSystem* ExplosionVFX;

	FTimerHandle DelayBeforeDestroy;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DelayDestroy = 2.f;

};
