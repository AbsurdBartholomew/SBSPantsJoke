#include <gba.h>

#include <maxmod.h>
#include "Menu.h"
#include <soundbank.h>
#include <soundbank_bin.h>
#include <string.h>
#include "Mem.h"
#include "State.h"
#include "Level.h"

#include <start.h>

void InitMenu()
{
	mmStart(MOD_TITLEMUSIC, MM_PLAY_LOOP);
	
	REG_DISPCNT = MODE_0 | BG0_ON;
	REG_BG0CNT =  BG_CBB(0) | BG_SBB(28) | BG_256_COLOR | BG_SIZE_0 | BG_PRIORITY(3);
	
	memcpy(MEM_BG_PALETTE, startPal, startPalLen);

    memcpy(&MEM_TILE[0][0], startTiles, startTilesLen);
    memcpy(&MEM_SCREENBLOCKS[28][0], startMap, startMapLen);
}

void UpdateMenu()
{
	if(keysDown() & KEY_START)
	{
		gLevel = e_LEVEL1;
		InitLevel(e_LEVEL1);
	}
}

void RenderMenu()
{
	
}