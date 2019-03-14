// Fill out your copyright notice in the Description page of Project Settings.
#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "ActorPaperFlipbook.generated.h"

/**
 * 
 */
UENUM()
enum class ActorStatus : uint8 {
	//�ƶ�
	Walk,
	//����
	Idle,
	//����
	Attack,
	//��Ծ
	Jump
};

UCLASS(BlueprintType, meta = (DisplayThumbnail = "true"))
class NEVERSALVATION_API UActorPaperFlipbook: public UObject
{
	GENERATED_BODY()
public:
	UActorPaperFlipbook();
	~UActorPaperFlipbook();
	UPROPERTY(Category = Sprite, EditAnywhere, meta = (DisplayThumbnail = "true"))
	UPaperFlipbook *sourceFile;
private:
	UPROPERTY(Category = Sprite, EditAnywhere, meta = (DisplayThumbnail = "true"))
	ActorStatus DrinkingStyle = ActorStatus::Idle;
};
