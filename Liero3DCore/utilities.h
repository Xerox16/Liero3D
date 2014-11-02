#ifndef _LIERO_3D_UTILITIES_
#define _LIERO_3D_UTILITIES_

#include <irrlicht.h>
#include <string>

	//throws BasicException if creation of irrlicht device fails
irr::IrrlichtDevice* initialize(int widht, int height, int fullscreen, irr::IEventReceiver* eventReceiver);

class CConverter
{
public:
	CConverter();
	~CConverter();

	const wchar_t* strToWchart(std::string sInput);
	const std::string wchartToStr(const wchar_t* wInput);
private:
	wchar_t* m_wCharBuffer = NULL;

};

struct IrrlichtHelper {
	irr::IrrlichtDevice* device;	//irrlicht main device
	irr::video::IVideoDriver* driver; //video driver
	irr::scene::ISceneManager* smgr; //scene manager
	irr::gui::IGUIEnvironment* gui; //gui
};


#endif
