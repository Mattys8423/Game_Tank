#include "Pawns/Tower.h"
#include "Pawns/Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


ATower::ATower() {
	BaseMesh->BodyInstance.bLockXRotation = true;
	BaseMesh->BodyInstance.bLockYRotation = true;
	BaseMesh->BodyInstance.bLockZRotation = true;
	BaseMesh->BodyInstance.bLockXTranslation = true;
	BaseMesh->BodyInstance.bLockYTranslation = true;
	BaseMesh->BodyInstance.bLockZTranslation = true;

}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (InFireRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
		RotateGunAI(PlayerTank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		Fire();
	}
	
}

bool ATower::InFireRange()
{
	if (PlayerTank)
    {
    	float Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
    	if (Distance <= FireRange)
    	{
    		return true;
    	}
    }
	return false;
}