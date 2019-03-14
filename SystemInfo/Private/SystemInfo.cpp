#include "SystemInfoPrivatePCH.h"
#include "SystemInfo/Public/SystemInfo.h"

class FSystemInfo :public ISystemInfo {
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FSystemInfo, SystemInfo)
void FSystemInfo::StartupModule() {}
void FSystemInfo::ShutdownModule() {}