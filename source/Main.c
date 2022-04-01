#include <gba.h>
#include <maxmod.h>
#include <soundbank.h>
#include <soundbank_bin.h>

#include "State.h"
#include "Menu.h"
#include "Level.h"

GameLevel gLevel;
int Choice = 0;

int main()
{
	irqInit();

	irqSet(IRQ_VBLANK, mmVBlank);
	irqEnable(IRQ_VBLANK);
	mmInitDefault((mm_addr)soundbank_bin, 8);

	mmStart(MOD_CH112, MM_PLAY_LOOP);

	switch (gLevel)
	{
	case e_MENU:
		InitMenu();
		break;
	case e_LEVEL1:
		Choice++;
	case e_LEVEL2:
		Choice++;
	case e_LEVEL3:
		Choice++;
	case e_LEVEL4:
		Choice++;
	case e_LEVEL5:
		Choice++;
	case e_LEVEL6:
		Choice++;
		InitLevel(Choice);
		break;
	}

	Choice = 0;

	while (1)
	{
		mmFrame();
		scanKeys();

		switch (gLevel)
		{
		case e_MENU:
			UpdateMenu();
			break;
		case e_LEVEL1:
			Choice++;
		case e_LEVEL2:
			Choice++;
		case e_LEVEL3:
			Choice++;
		case e_LEVEL4:
			Choice++;
		case e_LEVEL5:
			Choice++;
		case e_LEVEL6:
			Choice++;
			ThinkLevel(Choice);
			break;
		}
		VBlankIntrWait();
	}
}