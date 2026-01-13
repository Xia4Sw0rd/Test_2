// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_1_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:


	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float HealthMax;
	//You might want to comment this when you come back.
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float HealthRecovery;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Credits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float CreditMax;



public:	
	
	UFUNCTION(BlueprintCallable)
	bool isAlive()const;

	UFUNCTION(BlueprintCallable)
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthMax() const;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsFullWallet() const;


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	//UFUNCTION(BlueprintCallable, Category = "Damage")
	//float HealthRecovery() const; //c2365

	//UFUNCTION(BlueprintCallable, Category = "Damage")
	//float DamageAmount() const; //c2365

//	UFUNCTION(BlueprintCallable)
//	float HealthRecovery() const;

	
	UPROPERTY(BlueprintAssignable);
	FOnHealthChanged OnHealthChanged;

	//UPROPERTY(BlueprintAssignable);
	//FOnHealthChanged OnCreditChanged;
	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor*InstigatorActor,float Delta);


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyCreditChange(AActor* InstigatorActor, float Delta);

	//UFUNCTION(BlueprintCallable, Category = "Attributes")
	//float DamageAmount() const;
	


	
		
};
