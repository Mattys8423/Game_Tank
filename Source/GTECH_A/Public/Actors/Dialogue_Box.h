// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dialogue_Box.generated.h"

class UBoxComponent;

UCLASS()
class GTECH_A_API ADialogue_Box : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogue_Box();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	int number = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	bool Has_activated = false;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void Set_HasActivated(bool Active);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Show_Dialogue();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeText(int number_of_dialogue);

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComp;

	/*UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,	bool bFromSweep, const FHitResult& SweepResult);*/
};
