// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class NEVERSALVATION_API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent * SphereComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent *ArrowComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* MySprite;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite)
		USceneComponent *SceneComponent;

	class USphereComponent* GetSphereComponent() const { return SphereComponent; }

	class UArrowComponent* GetArrowComponent() const { return ArrowComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//class UPaperFlipbookComponent *PaperFlipbookComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UPaperFlipbookComponent* GetMySprite() const { return MySprite; }
};
