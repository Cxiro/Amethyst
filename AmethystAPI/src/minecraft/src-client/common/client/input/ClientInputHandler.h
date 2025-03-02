#pragma once
#include "minecraft/src-deps/input/InputHandler.h"

class ClientInstance;
using IClientInstance = ClientInstance;

class ClientInputHandler {
public:
    ClientInstance* mClient;
    std::byte padding[8];
    InputHandler* mInputHandler;
};