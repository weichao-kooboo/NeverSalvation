#pragma once

#include "ModuleManager.h"

class ILibuvSupport :public IModuleInterface {
public:
	static inline ILibuvSupport& Get() {
		return FModuleManager::LoadModuleChecked<ILibuvSupport>("LibuvSupport");
	}
	static inline bool IsAvailable() {
		return FModuleManager::Get().IsModuleLoaded("LibuvSupport");
	}
};