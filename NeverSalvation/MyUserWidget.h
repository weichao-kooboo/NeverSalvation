// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEVERSALVATION_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMyUserWidget(const FObjectInitializer& objectInitializer);
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnBtnChangeImgClick();
private:
	UImage * HeroIcon;

	UTexture2D* TexHero1;
	UTexture2D* TexHero2;

	int ImgFlag;
};
