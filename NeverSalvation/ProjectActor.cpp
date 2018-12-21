// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectActor.h"


// Sets default values
AProjectActor::AProjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectActor::OnHit);		// set up a notification for when this component hits something blocking

																						// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 50.f;
	ProjectileMovement->MaxSpeed = 100.f;
	//如果想要抛出物不默认受重力影响,选择0,然后设置Velocity朝着坐标移动
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->Velocity = FVector(10.0f, 0.0f, 0.0f);
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MySprite"));
	if (MySprite) {
		MySprite->AttachTo(RootComponent);
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		MySprite->SetCollisionProfileName(CollisionProfileName);
	}

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}


void AProjectActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}