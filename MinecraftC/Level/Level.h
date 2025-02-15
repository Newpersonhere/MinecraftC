#pragma once
#include <stdbool.h>
#include "Tile/Block.h"
#include "NextTickListEntry.h"
#include "../MovingObjectPosition.h"
#include "../Utilities/List.h"
#include "../Utilities/Random.h"
#include "../Particle/ParticleManager.h"
#include "../Physics/AABB.h"
#include "../GUI/FontRenderer.h"
#include "../Entity.h"
#include "Generator/LevelGenerator.h"

typedef struct Level {
	int width, height, depth;
	uint8_t * blocks;
	int xSpawn, ySpawn, zSpawn;
	float spawnRotation;
	struct LevelRenderer * renderer;
	int * lightBlockers;
	RandomGenerator random;
	int randomValue;
	List(NextTickListEntry) tickList;
	int waterLevel;
	uint32_t skyColor;
	uint32_t fogColor;
	uint32_t cloudColor;
	int unprocessed;
	int tickCount;
	Entity * player;
	List(Entity *) entities;
	ParticleManager * particleEngine;
	LevelGenerator generator;
	ProgressBarDisplay * progressBar;
#if MINECRAFTC_MODS
	uint8_t * distanceField;
#endif
} Level;

void LevelCreate(Level * level, ProgressBarDisplay * progressBar, int size);
void LevelRegenerate(Level * level, int size);
bool LevelLoad(Level * level, char * filePath);
bool LevelSave(Level * level, char * filePath, char * name);
void LevelSetData(Level * level, int w, int d, int h, uint8_t * blocks);
#if MINECRAFTC_MODS
void LevelCreateDistanceField(Level * level);
void LevelDestroyDistanceField(Level * level);
#endif
void LevelFindSpawn(Level * level);
void LevelCalculateLightDepths(Level * level, int x0, int y0, int x1, int y1);
void LevelSetRenderer(Level * level, struct LevelRenderer * listener);
bool LevelIsLightBlocker(Level * level, int x, int y, int z);
List(AABB) LevelGetCubes(Level * level, AABB box);
void LevelSwap(Level * level, int x0, int y0, int z0, int x1, int y1, int z1);
bool LevelSetTile(Level * level, int x, int y, int z, BlockType tile);
bool LevelSetTileNoNeighborChange(Level * level, int x, int y, int z, BlockType tile);
void LevelUpdateNeighborsAt(Level * Level, int x, int y, int z, BlockType tile);
bool LevelSetTileNoUpdate(Level * level, int x, int y, int z, BlockType tile);
bool LevelIsLit(Level * level, int x, int y, int z);
BlockType LevelGetTile(Level * level, int x, int y, int z);
bool LevelIsSolidTile(Level * level, int x, int y, int z);
void LevelTickEntities(Level * level);
void LevelTick(Level * level);
bool LevelIsInBounds(Level * level, int x, int y, int z);
float LevelGetGroundLevel(Level * level);
float LevelGetWaterLevel(Level * level);
bool LevelContainsAnyLiquid(Level * level, AABB box);
bool LevelContainsLiquid(Level * level, AABB box, LiquidType liquidID);
void LevelAddToNextTick(Level * level, int x, int y, int z, BlockType tile);
bool LevelIsSolidSearch(Level * level, float x, float y, float z, float radius);
int LevelGetHighestTile(Level * level, int x, int z);
void LevelSetSpawnPosition(Level * level, int x, int y, int z, float rotation);
float LevelGetBrightness(Level * level, int x, int y, int z);
bool LevelIsWater(Level * level, int x, int y, int z);
MovingObjectPosition LevelClip(Level * level, Vector3D v0, Vector3D v1);
void LevelPlaySound(Level * level, char * sound, Entity * entity, float volume, float pitch);
void LevelPlaySoundAt(Level * level, char * sound, float x, float y, float z, float volume, float pitch);
bool LevelMaybeGrowTree(Level * level, int x, int y, int z);
Entity * LevelGetPlayer(Level * level);
void LevelAddEntity(Level * level, Entity * entity);
void LevelRenderEntities(Level * level, TextureManager * textures, float dt);
void LevelExplode(Level * level, float x, float y, float z, float radius);
Entity * LevelFindPlayer(Level * level);
void LevelDestroy(Level * level);
