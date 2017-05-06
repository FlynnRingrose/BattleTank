// Flynn's rad copyright.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    //Sets a throttle between -1 and +1.
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);
	
    //Max force per track in newtons.
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000; //Assume a 40 tonne tank and 1g acceleration.
    
private:
    UTankTrack();
    
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void ApplySidewaysForce();
    
    void DriveTrack();
    
    float CurrentThrottle = 0.f;
};
