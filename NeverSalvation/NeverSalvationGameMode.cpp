// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NeverSalvationGameMode.h"
#include "NeverSalvationCharacter.h"
#include "LibuvSupport/Public/LibuvSupport.h"
#include "uv.h"
#include "LibuvSupport/Public/TcpClient.h"
#include "SystemInfo/Public/SystemInfoClient.h"

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
	tcp = new TcpClient("127.0.0.1", 7000);
	tcp->setCloseCallBack(on_close);
	tcp->setWriteCallBack(echo_write);
	tcp->connect();
}

ANeverSalvationGameMode::ANeverSalvationGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ANeverSalvationCharacter::StaticClass();	

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

}
