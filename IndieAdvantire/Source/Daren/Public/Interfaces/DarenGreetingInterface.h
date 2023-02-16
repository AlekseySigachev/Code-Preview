// Copyright TimeLine Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DarenGreetingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDarenGreetingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAREN_API IDarenGreetingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnGreetings();
	
};
