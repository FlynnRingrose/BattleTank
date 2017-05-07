// Flynn's rad copyright.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth; //Casts these ints into floats.
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
    //Convert floating point damage to integer.
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
    
    CurrentHealth -= DamageToApply;
    if (CurrentHealth <= 0)
    {
        OnDeath.Broadcast();
    }
    return DamageToApply;
}
