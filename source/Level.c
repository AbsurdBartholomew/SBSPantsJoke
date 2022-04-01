#include "Level.h"
#include "State.h"
#include <gba.h>
#include <gba_video.h>
#include <gba_sprites.h>
#include "Mem.h"
#include <maxmod.h>
#include <soundbank.h>
#include <soundbank_bin.h>
#include <spongebob.h>

#include <krab.h>
#include <kitchen.h>
#include <spat.h>
#include <something.h>
#include <finish.h>
#include <complete.h>

typedef struct
{
	u16 *sprData;
	u16 *palData;

	u16 sprLen;
	u16 palLen;

	int posX;
	int posY;
	
	int velX;
	int velY;

	OBJATTR *obj;
} SpongeBob;

int gSelLevel = e_LEVEL1;

SpongeBob gSpongeBob;

int maxSpeed = 5;

int speedX = 2;
int speedY = 2;

int newPosX = 0;
int newPosY = -SCREEN_HEIGHT;

int slowdown = 16;

void InitSpongeBob()
{
	gSpongeBob.obj = &OAM[0];
	gSpongeBob.sprData = spongebobTiles;
	gSpongeBob.sprLen = spongebobTilesLen;
	
	gSpongeBob.palData = spongebobPal;
	gSpongeBob.palLen = spongebobPalLen;
	
	gSpongeBob.posX = 0;
	gSpongeBob.posY = -SCREEN_HEIGHT;
	
	newPosX = 0;
	newPosY = -SCREEN_HEIGHT;

	gSpongeBob.obj->attr0 =
		// Y coordinate
		OBJ_Y(gSpongeBob.posY) |
		// Disable rotoscale mode
		ATTR0_TYPE_NORMAL |
		// Use a 16-color palette
		ATTR0_COLOR_16 |
		// Object shape
		ATTR0_SQUARE;

	gSpongeBob.obj->attr1 =
		// X coordinate
		OBJ_X(gSpongeBob.posX) |
		// Object size
		ATTR1_SIZE_32;

	gSpongeBob.obj->attr2 =
		// Tile index of the tiles in SPRITE_GFX memory
		OBJ_CHAR(16) |
		// Which palette index to use (not needed for 256-color sprites)
		ATTR2_PALETTE(1) |
		// Priority relative to other layers (sprites and backgrounds)
		ATTR2_PRIORITY(1);

	uint16_t *spr_pal_2 = SPRITE_PALETTE + (1 * 16);
	CpuSet(gSpongeBob.palData, spr_pal_2, COPY32 | (gSpongeBob.palLen / 4));


	uint8_t *spr_tiles = (uint8_t *)SPRITE_GFX + (16 * TILE_SIZE);
	CpuSet(gSpongeBob.sprData, spr_tiles, COPY32 | (gSpongeBob.sprLen / 4));
	
	REG_DISPCNT = MODE_0 | BG0_ON | OBJ_ON | OBJ_1D_MAP;
}

void ThinkSpongeBob()
{
	if(keysHeld() & KEY_UP)
	{	
		newPosY -= speedY;
	}
	else if(keysHeld() & KEY_DOWN)
	{
		newPosY += speedY;
	}
	
	if(keysHeld() & KEY_LEFT)
	{
		newPosX -= speedX;
	}
	if(keysHeld() & KEY_RIGHT)
	{
		newPosX += speedX;
	}
	
	gSpongeBob.posY = ((gSpongeBob.posY * (slowdown - 1)) + newPosY) / slowdown;
	gSpongeBob.posX = ((gSpongeBob.posX * (slowdown - 1)) + newPosX) / slowdown;
	
	gSpongeBob.obj->attr0 =
		// Y coordinate
		OBJ_Y(gSpongeBob.posY) |
		// Disable rotoscale mode
		ATTR0_TYPE_NORMAL |
		// Use a 16-color palette
		ATTR0_COLOR_16 |
		// Object shape
		ATTR0_SQUARE;

	gSpongeBob.obj->attr1 =
		// X coordinate
		OBJ_X(gSpongeBob.posX) |
		// Object size
		ATTR1_SIZE_32;
		
	// check collision
	if(gSpongeBob.posX >= 203 - 64 && gSpongeBob.posY <= 18 - 64)
	{
		gSelLevel++;
		InitLevel(gSelLevel);
	}
}

void InitLevel(int level)
{
	InitSpongeBob();
	
	switch (level)
	{
	case e_LEVEL1:
		mmStart(MOD_CH112, MM_PLAY_LOOP);
		
		memcpy(MEM_BG_PALETTE, krabPal, krabPalLen);

		memcpy(&MEM_TILE[0][0], krabTiles, krabTilesLen);
		memcpy(&MEM_SCREENBLOCKS[28][0], krabMap, krabMapLen);
		break;
	case e_LEVEL2:
		mmStart(MOD_CH513, MM_PLAY_LOOP);
		
		memcpy(MEM_BG_PALETTE, kitchenPal, kitchenPalLen);

		memcpy(&MEM_TILE[0][0], kitchenTiles, kitchenTilesLen);
		memcpy(&MEM_SCREENBLOCKS[28][0], kitchenMap, kitchenMapLen);
		break;
	case e_LEVEL3:
		mmStart(MOD_CH1B, MM_PLAY_LOOP);
		
		memcpy(MEM_BG_PALETTE, spatPal, spatPalLen);

		memcpy(&MEM_TILE[0][0], spatTiles, spatTilesLen);
		memcpy(&MEM_SCREENBLOCKS[28][0], spatMap, spatMapLen);
		break;
	case e_LEVEL4:
		mmStart(MOD_CH41, MM_PLAY_LOOP);
		
		memcpy(MEM_BG_PALETTE, somethingPal, somethingPalLen);

		memcpy(&MEM_TILE[0][0], somethingTiles, somethingTilesLen);
		memcpy(&MEM_SCREENBLOCKS[28][0], somethingMap, somethingMapLen);
		break;
	case e_LEVEL5:
		mmStart(MOD_CH5B, MM_PLAY_LOOP);
		
		memcpy(MEM_BG_PALETTE, finishPal, finishPalLen);

		memcpy(&MEM_TILE[0][0], finishTiles, finishTilesLen);
		memcpy(&MEM_SCREENBLOCKS[28][0], finishMap, finishMapLen);
		break;
	case e_LEVEL6:
		mmStart(MOD_CH323, MM_PLAY_LOOP);
		
		memcpy(MEM_BG_PALETTE, completePal, completePalLen);

		memcpy(&MEM_TILE[0][0], completeTiles, completeTilesLen);
		memcpy(&MEM_SCREENBLOCKS[28][0], completeMap, completeMapLen);
		
		gSpongeBob.posX = -512;
		gSpongeBob.posY = -512;
		speedX = 0;
		speedY = 0;
		newPosX = -512;
		newPosY = -512;
		break;
	}
}

void ThinkLevel(int level)
{
	ThinkSpongeBob();
	
	if(keysDown() & KEY_R)
	{
		gSelLevel++;
		InitLevel(gSelLevel);
	}
}