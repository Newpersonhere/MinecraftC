#pragma once
#include "Block.h"

typedef Block FlowerBlock;

void FlowerBlockCreate(FlowerBlock * block, BlockType type, int textureID, TileSound sound, float particleGravity);
void FlowerBlockUpdate(FlowerBlock * block, struct Level * level, int x, int y, int z, RandomGenerator * random);
AABB FlowerBlockGetCollisionAABB(FlowerBlock * block, int x, int y, int z);
bool FlowerBlockIsOpaque(FlowerBlock * block);
bool FlowerBlockIsSolid(FlowerBlock * block);
void FlowerBlockRenderPreview(FlowerBlock * block);
bool FlowerBlockIsCube(FlowerBlock * block);
bool FlowerBlockRender(FlowerBlock * block, struct Level * level, int x, int y, int z);
void FlowerBlockRenderFullBrightness(FlowerBlock * block);
