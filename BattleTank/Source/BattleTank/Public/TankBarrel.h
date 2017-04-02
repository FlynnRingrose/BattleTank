// Flynn's rad copyright.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) //This allows us to access Tank Barrel as a custom component within Unreal.
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    //-1 is max downward movement, and +! is max upward movement.
    void Elevate(float RelativeSpeed);
    
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 20; //Sensible default. These can be edited in Unreal.
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees = 40;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees = 0;
};
