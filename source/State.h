#ifndef _STATE_H
#define _STATE_H

#include <gba.h>

typedef struct
{
	u8 mSFXVolume;
	u8 mMusicVolume;
	u8 mControllerMethod;
} GameParams;

enum
{
	e_MENU,
	e_LEVEL1,
	e_LEVEL2,
	e_LEVEL3,
	e_LEVEL4,
	e_LEVEL5,
	e_LEVEL6
};
typedef u16 GameLevel;

extern GameLevel gLevel;

#endif