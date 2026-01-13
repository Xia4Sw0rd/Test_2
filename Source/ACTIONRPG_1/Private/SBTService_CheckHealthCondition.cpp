// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckHealthCondition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"
#include "AIController.h"



USBTService_CheckHealthCondition::USBTService_CheckHealthCondition()
{

	LowHealthFraction = 0.5f;
	
}




void USBTService_CheckHealthCondition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ensure(AIPawn))
	{
	
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIPawn);
		if(ensure(AttributeComp))
		{
		
			bool bLowHealth = (AttributeComp->GetHealth() / AttributeComp->GetHealthMax()) < LowHealthFraction;


			UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

			BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
		
		
		
		}
	
	
	
	}

	//Constantly check on AI's health and act accordingly.


}




