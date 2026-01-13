// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUCoin.generated.h"


class USphereComponent;
class UStaticMeshComponent;
class USAttributeComponent;
class UPrimitiveComponent;





UCLASS()
class ACTIONRPG_1_API ASUCoin : public AActor
{
	GENERATED_BODY()
	

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Currency")
	int CoinValue;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	ASUCoin();
};
