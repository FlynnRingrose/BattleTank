// Flynn's rad copyright.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    //No need to call Super as we're replacing the functionality.
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); //The unit vector of the tank's current direction.
    auto AIForwardIntention = MoveVelocity.GetSafeNormal(); //The unit vector of the direction the tank needs to go.
    
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);
    
    auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure (LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) //Throw is like thrust.
{
    if (!ensure (LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
