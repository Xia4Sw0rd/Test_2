// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"
#include "SUCharacter.h"
#include "Components/SphereComponent.h"
#include "SAttributeComponent.h"


// Sets default values
ASPowerUpActor::ASPowerUpActor()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Power Up");
	RootComponent = SphereComp;


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	float Healthrecovery = 10.0f;
	



 
}


void ASPowerUpActor::OnActorOverlap(UPrimitiveComponent*OverlappedComponent,AActor*OtherActor,UPrimitiveComponent*OtherComp,int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		//Line 38 had an error due to Attribute Comp being hidden (Error c4458). Had to lowercase it to get this to work.
		//Healing mechanic for player when he touches the potion.
		USAttributeComponent* attributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp) {
		//	float HealthRecovery = 10.0f;
			AttributeComp->ApplyHealthChange(GetInstigator(),HealthRecovery);
			
			
			Destroy();


		}
	
	
	}














}

void ASPowerUpActor::BeginPlay(){

	Super::BeginPlay();


}


void ASPowerUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
