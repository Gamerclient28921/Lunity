#include "pch.h"
#include "RenderHook.h"
#include "../../SDK/LunMem.h"
#include "../../SDK/LunMC.h"
#include "../../SDK/DrawUtils.h"
#include "../../Logger.h"
#include "../CheatManager.h"
#include <MinHook.h>
#include "../CheatManager.cpp"
#include "../../SDK/DrawUtils.cpp"
#pragma comment(lib, "libMinHook.lib")

typedef int (__stdcall* RenderText)(__int64 a1, MinecraftUIRenderContext* renderCtx);
RenderText original;

float entireW = 0;
int hookCallback(__int64 a1, MinecraftUIRenderContext* renderCtx) {
	DrawUtils::setCtx(renderCtx, LunMem::getClientInstance()->getGuiData());

	//CheatManager::onPreRender();

	//DrawUtils::flush();
	int ret = original(a1, renderCtx);

	CheatManager::onPostRender();

	//Logger::logHex("Context", (ulong)renderCtx);

	DrawUtils::fillRectangle(Vector4(0, 0, 100, 100), Color(1, 1, 1, 1), 1);
	DrawUtils::drawText(Vector2(1, 1), new string("Test"), nullptr, 1);

	DrawUtils::flush();
	return ret;
}

void RenderHook::installHook() {
	Logger::log("installing render hook...");
	uintptr_t toHook = LunMem::FindSignature("48 8B C4 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 48 89 58 18 0F 29 70 B8 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 89 54 24 ? 4C 8B E1 48 89 4C 24 ?");
	Logger::logHex("ToHook", (ulong)toHook);
	bool installSuccess = false;
	if (MH_CreateHook((void*)toHook, &hookCallback, reinterpret_cast<LPVOID*>(&original)) == MH_OK) {
		Logger::log("Render Hook successfully created!");
		if (MH_EnableHook((void*)toHook) == MH_OK) {
			installSuccess = true;
			Logger::log("render hook installed");
		}
	}
	if (!installSuccess) {
		Logger::log("Failed to hook render!");
	}
}

void RenderHook::uninstallHook()
{
	void* toHook = (void*)(LunMem::getBaseModule() + 0x7652A0);
	MH_DisableHook(toHook);
}
