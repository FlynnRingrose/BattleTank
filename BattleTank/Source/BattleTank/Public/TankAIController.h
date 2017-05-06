// Flynn's rad copyright.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
    
protected: //Protected variables can be read by children of the class.
    //How close can the AI tank get?
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 8000;
	
private:
    
    virtual void BeginPlay() override;
    
    virtual void Tick( float DeltaSeconds ) override;
};
