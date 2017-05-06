// Flynn's rad copyright.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
//Depends on movement component via pathfinding system.

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if (!ensure(PlayerTank && ControlledTank)) { return; }
    
    //TODO Move towards the player.
    MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in CM.
        
    //Aim towards the player.
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    if(AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire(); //TODO Limit firing rate.
    }
}
