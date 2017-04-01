// Flynn's rad copyright.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

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
