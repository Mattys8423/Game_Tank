#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// GENERATED .H = DERNIER INCLUDE
#include "BasePawn.generated.h"

class AProjectile;
// FORWARD DECLARATION
class UBoxComponent;
class USoundCue;


UCLASS()
class GTECH_A_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* Explosion;

	UPROPERTY(EditAnywhere, Category = "Canon properties");
	float CoolDown = 0.f;

protected:
	virtual void BeginPlay() override;
	void RotateTurret(FVector LookAtTarget);
	void RotateGunAI(FVector LookAtTarget);

	UPROPERTY(EditAnywhere, Category = "Canon properties");
	float InterpSpeed = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Canon properties");
	float Base_CD = 5.f;

	UPROPERTY(EditAnywhere, Category = "Turret Rotation")
	float MinPitch = -10.0f;

	UPROPERTY(EditAnywhere, Category = "Turret Rotation")
	float MaxPitch = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	void Fire();	

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat Properties")
	FVector ProjectileScale = FVector(5.f, 5.f, 5.f);

	UPROPERTY(EditAnywhere, Category = "Combat Properties")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat Properties")
	USoundCue* FireSFX;

};
