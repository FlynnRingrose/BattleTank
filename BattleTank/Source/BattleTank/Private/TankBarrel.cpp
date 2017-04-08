// Flynn's rad copyright.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    //Move the barrel the right amount this frame.
    //Given a maximum elevation speed and frame time.
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; //RelativeRotation is a property of the Scene Component.
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees); //Explicitly works on floats as specified.
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}
