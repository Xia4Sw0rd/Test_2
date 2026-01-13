// Fill out your copyright notice in the Description page of Project Settings.


#include "SUCoin.h"
#include "Components/SphereComponent.h"
#include "SUCharacter.h"
#include "SAttributeComponent.h"
#include "SPowerUpActor.h"
//#include "AI/SAICharacter.h"
//#include "STargetDummy.h"

// Sets default values
ASUCoin::ASUCoin()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Power Up");
	RootComponent = SphereComp;


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");


	int Coinvalue = 0;
}




void ASUCoin::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


	if(OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* attributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp) {
			//	float HealthRecovery = 10.0f;
			AttributeComp->ApplyCreditChange(GetInstigator(), +CoinValue);


			Destroy();


		}
	
	
	
	
	
	
	
	
	}










}















// Called when the game starts or when spawned
void ASUCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASUCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

