#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class GTECH_A_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	void RotateGunUp();
	void RotateGunDown();

	UFUNCTION(BlueprintCallable, Category = "Canon properties")
	float GetCoolDown() const;

	UFUNCTION(BlueprintCallable, Category = "Canon properties")
	float GetBase_CD() const;

	UFUNCTION(BlueprintCallable, Category = "Tank")
	UStaticMeshComponent* GetBaseMesh() const { return this->BaseMesh; }

	UFUNCTION(BlueprintCallable, Category = "Tank")
	void SetCamera(bool Active);

	UFUNCTION(BlueprintCallable, Category = "Tank")
	void SetCamera_Turret(bool Active);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimZoomAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateGunUpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateGunDownAction;

	void Move(const FInputActionValue& Value);
	void Aim();
	void AdjustFOV(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActivateAim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DeactivateAim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowReload();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RemoveReload();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Truck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* L_truck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* R_truck;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> Wheels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera_Turret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed = 1500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 100.f;

	UPROPERTY(EditAnywhere, Category = "Canon properties");
	bool Is_aiming = false;

	UPROPERTY(EditAnywhere, Category = "Canon properties")
	float CurrentGunPitch = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Camera_Zoom")
	float ZoomSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Camera_Zoom")
	float MaxFOV = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Camera_Zoom")
	float MinFOV = 30.0f;

	APlayerController* TankPlayerController;
	
};
