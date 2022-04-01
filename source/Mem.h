#ifndef _MEM_H
#define _MEM_H

#include <gba.h>

typedef u16 ScreenBlock[1024];
typedef u16 Tile[32];
typedef Tile TileBlock[256];

#define TILE_SIZE (4 * 8 * 8) / 8

#define MEM_VRAM                ((volatile u32*)VRAM)
#define MEM_TILE                ((TileBlock*)VRAM)
#define MEM_SCREENBLOCKS        ((ScreenBlock*)VRAM)

#define MEM_BG_PALETTE          ((u16*)(0x05000000))

#define BG_CBB_MASK		0x000C
#define BG_CBB_SHIFT		 2
#define BG_CBB(n)		((n)<<BG_CBB_SHIFT)

#define BG_SBB_MASK		0x1F00
#define BG_SBB_SHIFT		 8
#define BG_SBB(n)		((n)<<BG_SBB_SHIFT)

#endif