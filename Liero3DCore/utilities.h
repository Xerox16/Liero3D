#ifndef _LIERO_3D_UTILITIES_
#define _LIERO_3D_UTILITIES_

#include <irrlicht.h>

class IrrlichtUtilities
{
public:
	static irr::IrrlichtDevice* initialize(int widht, int height, int fullscreen, irr::IEventReceiver* eventReceiver);
};

#endif