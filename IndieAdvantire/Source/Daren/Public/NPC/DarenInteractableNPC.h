// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interfaces/DarenInteractInterface.h"
#include "NPC/DarenNPCBase.h"
#include "DarenInteractableNPC.generated.h"

/**
 * 
 */
UCLASS()
class DAREN_API ADarenInteractableNPC : public ADarenNPCBase, public  IDarenInteractInterface
{
	GENERATED_BODY()

public:
	ADarenInteractableNPC();
	virtual void OnInteract() override;
protected:
private:

	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametrs|Behaviour", DisplayName = "Action Behaviour")
	UBehaviorTree* BTAction;
protected:



private:
};
