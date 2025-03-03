#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class GTECH_A_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	ATank* PlayerTank;

	UPROPERTY(EditAnywhere, Category = "Canon Properties")
	float FireRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Canon Properties")
	float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();

	bool InFireRange();
};
