#pragma once
#include "minecraft/src/common/nbt/Tag.h"
#include <cstdint>

class Int64Tag : public Tag {
public:
    int64_t data;
};