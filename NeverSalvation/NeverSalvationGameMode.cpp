// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NeverSalvationGameMode.h"
#include "NeverSalvationCharacter.h"
#include "LibuvSupport/Public/LibuvSupport.h"
#include "uv.h"
#include "LibuvSupport/Public/TcpClient.h"
#include "SystemInfo/Public/SystemInfoClient.h"
#include "Blueprint/UserWidget.h"

#pragma comment(lib,"libuv.lib")
/*
void on_close(uv_handle_t* handle) {
	printf("close");
	free(handle);
}
void echo_write(uv_write_t *req, int status) {
	if (status) {
		fprintf(stderr, "Write error %s\n", uv_strerror(status));
	}
	//free_write_req(req);
}
*/

UUserWidget *MyWidgetInstance;

void on_close(uv_handle_t* handle) {
	printf("close");
	free(handle);
}
void echo_write(uv_write_t *req, int status) {
	if (status) {
		fprintf(stderr, "Write error %s\n", uv_strerror(status));
	}
	//free_write_req(req);
}
class TcpClient *tcp;
void hare(void *arg) {
	tcp = new TcpClient("192.168.11.138", 2019);
	tcp->setCloseCallBack(on_close);
	tcp->setWriteCallBack(echo_write);
	tcp->connect();
}

ANeverSalvationGameMode::ANeverSalvationGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ANeverSalvationCharacter::StaticClass();	

	MyWidgetInstance = NULL;
	
	uv_thread_t hare_id;
	uv_thread_create(&hare_id, hare, NULL);
	Sleep(2000);
	SystemInfoClient *sic = new SystemInfoClient();
	tcp->write(sic->getOsInfo());
	tcp->write(sic->getCpuInfo());
	tcp->write(sic->getMemoryInfo());
	tcp->write(sic->getHardDiskInfo());
	delete sic;
}

void ANeverSalvationGameMode::BeginPlay() {
	if (MyWidgetInstance)
	{
		MyWidgetInstance->RemoveFromViewport();
		MyWidgetInstance = nullptr;
	}

	//加载自定义UMG的class，通过这个class创建Widget对象，并显示在界面中。
	if (UClass* MyWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/2DSideScrollerCPP/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C'")))
	{
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			MyWidgetInstance = CreateWidget<UUserWidget>(PC, MyWidgetClass);
			if (MyWidgetInstance)
			{
				MyWidgetInstance->AddToViewport();
			}
		}
	}
}
