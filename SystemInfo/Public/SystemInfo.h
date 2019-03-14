#pragma once

#include "ModuleManager.h"

class ISystemInfo :public IModuleInterface {
public:
	static inline ISystemInfo& Get() {
		return FModuleManager::LoadModuleChecked<ISystemInfo>("SystemInfo");
	}
	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("SystemInfo");
	}
};