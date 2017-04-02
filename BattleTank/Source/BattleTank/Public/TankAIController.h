// Flynn's rad copyright.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    
    virtual void BeginPlay() override;
    
    virtual void Tick( float DeltaSeconds ) override;
    
private:
    
    ATank* GetControlledTank() const;
    
    ATank* GetPlayerTank() const;
};
