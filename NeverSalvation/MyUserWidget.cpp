// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"

UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer) {
	HeroIcon = NULL;
	TexHero1 = NULL;
	TexHero2 = NULL;
	ImgFlag = 0;
}

void UMyUserWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (UImage *img = Cast<UImage>(GetWidgetFromName(FName(TEXT("ImgHero"))))) {
		HeroIcon = img;
	}

	//根据组件ID查找Button组件，并为其添加Click回调事件
	if (UButton* btn = Cast<UButton>(GetWidgetFromName("BtnChangeImg")))
	{
		FScriptDelegate Del;
		Del.BindUFunction(this, "OnBtnChangeImgClick");
		btn->OnClicked.Add(Del);
	}

	//加载图片资源
	if (TexHero1)
	{
		//如果已经加载过，则先销毁掉
		TexHero1->ConditionalBeginDestroy();
		TexHero1 = NULL;
		GetWorld()->ForceGarbageCollection(true);
	}
	TexHero1 = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/pic_01.pic_01'"));

	if (TexHero2)
	{
		TexHero2->ConditionalBeginDestroy();
		TexHero2 = NULL;
		GetWorld()->ForceGarbageCollection(true);
	}
	TexHero2 = LoadObject<UTexture2D>(NULL, TEXT("Texture2D'/Game/pic_02.pic_02'"));
}

void UMyUserWidget::OnBtnChangeImgClick()
{
	//切换显示图片
	if (HeroIcon && TexHero1 && TexHero2)
	{
		HeroIcon->SetBrushFromTexture(ImgFlag ? TexHero1 : TexHero2);
		ImgFlag = ImgFlag == 0 ? 1 : 0;
	}
}