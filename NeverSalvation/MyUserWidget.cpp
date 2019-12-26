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

	//�������ID����Button�������Ϊ�����Click�ص��¼�
	if (UButton* btn = Cast<UButton>(GetWidgetFromName("BtnChangeImg")))
	{
		FScriptDelegate Del;
		Del.BindUFunction(this, "OnBtnChangeImgClick");
		btn->OnClicked.Add(Del);
	}

	//����ͼƬ��Դ
	if (TexHero1)
	{
		//����Ѿ����ع����������ٵ�
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
	//�л���ʾͼƬ
	if (HeroIcon && TexHero1 && TexHero2)
	{
		HeroIcon->SetBrushFromTexture(ImgFlag ? TexHero1 : TexHero2);
		ImgFlag = ImgFlag == 0 ? 1 : 0;
	}
}