// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera_Tuto.generated.h"

class UCameraComponent;

UCLASS()
class GTECH_A_API ACamera_Tuto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamera_Tuto();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tuto")
	int number = 0.f;

	UFUNCTION(BlueprintCallable, Category = "Tuto")
	void ActivateCamera(float number_of_camera);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float TargetFOV = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float FOVInterpSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	bool Is_zoom = false;
};
