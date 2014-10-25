#include <irrlicht.h>

#include <boost/log/trivial.hpp>

#include <math.h>
#include <sstream>

#include "utilities.h"
#include "config.h"
#include "event_receiver.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace scene;

enum {
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};

enum Menu {
    MENU_SINGLEPLAYER,
    MENU_MULTIPLAYER,
    MENU_OPTION
};

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext {
	IrrlichtDevice *device_;
	Menu id_;
};

// Define some values that we'll use to identify individual GUI controls.
enum {
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FILE_OPEN_BUTTON,
    GUI_ID_TRANSPARENCY_SCROLL_BAR,
    GUI_ID_SINGLEPLAYER_BUTTON,
    GUI_ID_MULTIPLAYER_BUTTON,
    GUI_ID_OPTION_BUTTON
};


ICameraSceneNode* camera = NULL;
ITriangleSelector* selector = NULL;


class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(SAppContext* context) : context_(context) { }

	virtual bool OnEvent(const SEvent& event) {
		if (event.EventType == EET_GUI_EVENT) {
			s32 id = event.GUIEvent.Caller->getID();

			switch(event.GUIEvent.EventType) {
			case EGET_BUTTON_CLICKED:
				switch(id) {

				case GUI_ID_SINGLEPLAYER_BUTTON:
					context_->id_ = MENU_SINGLEPLAYER;
					return true;

				case GUI_ID_MULTIPLAYER_BUTTON:
					context_->id_ = MENU_MULTIPLAYER;
					return true;

				case GUI_ID_OPTION_BUTTON:
					context_->id_ = MENU_OPTION;
					return true;
					
				case GUI_ID_QUIT_BUTTON:
					context_->device_->closeDevice();
					return true;

				default:
					return false;
				}
				break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext* context_;
};

int main()
{
	// create device
	EventReceiver receiver1;
	Configuration config;
	config.load("../assets/settings.json");

	IrrlichtDevice* device = IrrlichtUtilities::initialize(640, 480, 0, &receiver1);

	if (device == 0)
		return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();


	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

	env->addButton(rect<s32>(640/2 - 120, 140, 640/2 + 120, 190), 0, GUI_ID_SINGLEPLAYER_BUTTON,
	               L"Singleplayer", L"Heavy fights against the CPU");

	env->addButton(rect<s32>(640/2 - 120, 210, 640/2 + 120, 260), 0, GUI_ID_MULTIPLAYER_BUTTON,
	               L"Multiplayer", L"Not available yet");
	env->addButton(rect<s32>(640/2 - 120, 280, 640/2 + 120, 330), 0, GUI_ID_OPTION_BUTTON,
	               L"Options", L"Adjust ingame options");
	env->addButton(rect<s32>(640/2 - 120, 350, 640/2 + 120, 400), 0, GUI_ID_QUIT_BUTTON,
	               L"Quit", L"Exits Program");



	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device_ = device;

	// Then create the event receiver, giving it that context structure.
	MyEventReceiver receiver(&context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(&receiver);


	device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");

	scene::IAnimatedMesh* mesh = smgr->getMesh("../../media/20kdm2.bsp");
	scene::IMeshSceneNode* node = NULL;

	if(mesh) {
		node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	}


	if(node) {
		node->setPosition(core::vector3df(-1300, -144, -1249));
		selector = smgr->createOctreeTriangleSelector(node->getMesh(), node, 128);
		node->setTriangleSelector(selector);
	}

	camera = smgr->addCameraSceneNode();
	if(camera) {
		ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(vector3df(0,0,30), 20.0f);
		if(anim) {
			camera->addAnimator(anim);
			anim->drop();
		}
	}


	int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();


	while(device->run()) {
		if(context.id_ == MENU_SINGLEPLAYER) {
			//switch to ingame camera
			if(camera) {
				smgr->setActiveCamera(0);
				camera->remove();
			}

			camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
			camera->setPosition(vector3df(50, 50,-60));
			camera->setTarget(vector3df(-70,30,-60));

			if(selector) {
				scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
				                                      selector, camera, core::vector3df(30,50,30),
				            ;                          core::vector3df(0,-10,0), core::vector3df(0,30,0));
				selector->drop(); // As soon as we're done with the selector, drop it.
				camera->addAnimator(anim);
				anim->drop();  // And likewise, drop the animator when we're done referring to it.
			}

			device->getCursorControl()->setVisible(false);

			//delete gui
			env->clear();
		}

		driver->beginScene(true, true, video::SColor(255,80,80,80));

		smgr->drawAll(); // draw the 3d scene
		env->drawAll(); // draw the gui environment (the logo)

		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps) {
			core::stringw tmp(L"Movement Example - Irrlicht Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}

	device->drop();

	return 0;
}
