#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src/common/world/level/BlockPos.h"
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"
#include "minecraft/src-deps/core/headerIncludes/gsl_includes.h"

//is_virtual = True
//hide_vtable = False
//struct_size = 208
//
//# (Type, Name, Size (in bytes), Offset (in bytes))
//struct = [
//("gsl::not_null<BlockLegacy*>", "mLegacyBlock", 8, 0x30),
//]

using DataID = unsigned short;

class Block {
public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ std::byte padding8[40];
    /* this + 48  */ gsl::not_null<BlockLegacy*> mLegacyBlock;
    /* this + 56  */ std::byte padding56[152];
};

static_assert(sizeof(Block) == 208);