#include "hooks/Hooks.h"

SafetyHookInline _ScreenView_setupAndRender;
SafetyHookInline _ClientInstance_onStartJoinGame;
SafetyHookInline _ClientInstance_requestLeaveGame;
SafetyHookInline _Minecraft_update;
SafetyHookInline _VanillaItems_registerItems;

void* ScreenView_setupAndRender(ScreenView* self, UIRenderContext* ctx)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();
    events->onRenderUI.Invoke(self, ctx);
    return _ScreenView_setupAndRender.call<void*, ScreenView*, UIRenderContext*>(self, ctx);
}

int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();
    events->onStartJoinGame.Invoke(self);

    return _ClientInstance_onStartJoinGame.call<int64_t, ClientInstance*, int64_t, int64_t, uint64_t>(self, a2, a3, a4);
}

void ClientInstance_requestLeaveGame(ClientInstance* self, char switchScreen, char sync)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    events->onRequestLeaveGame.Invoke();

    _ClientInstance_requestLeaveGame.thiscall(self, switchScreen, sync);
}

bool Minecraft_update(Minecraft* self) {
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    bool value = _Minecraft_update.call<bool, Minecraft*>(self);
    events->update.Invoke();

    return value;
}

void* VanillaItems_registerItems(
    const ItemRegistryRef itemRegistry,
    const BaseGameVersion* baseGameVersion,
    const Experiments* experiments,
    void* enableExperimentalGameplay) 
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    // Allow Vanilla to register its own items first
    void* result = _VanillaItems_registerItems.fastcall<void*>(&itemRegistry, baseGameVersion, experiments, enableExperimentalGameplay);

    std::shared_ptr<ItemRegistry>* sharedRegistryPtr = new std::shared_ptr<ItemRegistry>();
    itemRegistry._lockRegistry(&sharedRegistryPtr);

    ItemRegistry* registry = sharedRegistryPtr->get();
    events->registerItems.Invoke(registry);

    return result;
}

 SafetyHookInline _BlockDefinitionGroup_registerBlocks;

void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    events->registerBlocks.Invoke(self);

    _BlockDefinitionGroup_registerBlocks.thiscall<void>(self);
}

void CreateModFunctionHooks() {
    HookManager* hookManager = AmethystRuntime::getHookManager();

    hookManager->RegisterFunction(&ScreenView::setupAndRender, "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 54 24 ? 4C 8B E9 48 89 4C 24");
    hookManager->CreateHook(&ScreenView::setupAndRender, _ScreenView_setupAndRender, &ScreenView_setupAndRender);
    
    hookManager->RegisterFunction(&Minecraft::update, "48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48");
    hookManager->CreateHook(&Minecraft::update, _Minecraft_update, &Minecraft_update);

    hookManager->RegisterFunction(&ClientInstance::onStartJoinGame, "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 45 8B F1");
    hookManager->CreateHook(&ClientInstance::onStartJoinGame, _ClientInstance_onStartJoinGame, &ClientInstance_onStartJoinGame);

    hookManager->RegisterFunction(&ClientInstance::requestLeaveGame, "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA");
    hookManager->CreateHook(&ClientInstance::requestLeaveGame, _ClientInstance_requestLeaveGame, &ClientInstance_requestLeaveGame);

    hookManager->RegisterFunction(&VanillaItems::registerItems, "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24");
    hookManager->CreateHook(&VanillaItems::registerItems, _VanillaItems_registerItems, &VanillaItems_registerItems);

    hookManager->RegisterFunction(&BlockDefinitionGroup::registerBlocks, "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4C 8B F9");
    hookManager->CreateHook(&BlockDefinitionGroup::registerBlocks, _BlockDefinitionGroup_registerBlocks, &BlockDefinitionGroup_registerBlocks);
}