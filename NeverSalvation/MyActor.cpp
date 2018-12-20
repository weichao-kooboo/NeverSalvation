// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "PaperFlipbookComponent.h"
#include "NeverSalvationCharacter.h"


void AMyActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent
	, AActor * OtherActor
	, UPrimitiveComponent * OtherComp
	, int32 OtherBodyIndex
	, bool bFromSweep
	, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		ANeverSalvationCharacter *player = Cast<ANeverSalvationCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (player) {
			Destroy();
		}
	}
}

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	this->RootComponent = SceneComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->bGenerateOverlapEvents = true;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnOverlapBegin);
	SphereComponent->AttachToComponent(RootComponent,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	//PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	MySprite = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	if (MySprite)
	{
		MySprite->AlwaysLoadOnClient = true;
		MySprite->AlwaysLoadOnServer = true;
		MySprite->bOwnerNoSee = false;
		MySprite->bAffectDynamicIndirectLighting = true;
		MySprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		MySprite->SetupAttachment(GetSphereComponent());
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		MySprite->SetCollisionProfileName(CollisionProfileName);
		MySprite->bGenerateOverlapEvents = false;
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

