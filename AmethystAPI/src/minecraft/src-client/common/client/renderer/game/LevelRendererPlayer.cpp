#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.h"

float LevelRendererPlayer::getFov(float originalFov, bool applyEffects) {
    using function = float(__thiscall*)(LevelRendererPlayer*, float, bool);
    static auto func = reinterpret_cast<function>(SigScan("48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05"));
    return func(this, originalFov, applyEffects);
}