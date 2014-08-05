#include <irrlicht.h>
#include <boost/log/trivial.hpp>
#include "utilities.h"
#include "event_receiver.h"

using namespace irr;

int main()
{
	// create device
	EventReceiver receiver;

	IrrlichtDevice* device = IrrlichtUtilities::initialize(640, 480, 0, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	scene::ISceneNode * node = smgr->addSphereSceneNode();
	if (node) {
		node->setPosition(core::vector3df(0,0,30));
		node->setMaterialTexture(0, driver->getTexture("/home/xerox/Programmierung/Bibliotheken/irrlicht-1.8.1/media/wall.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	scene::ISceneNode* n = smgr->addCubeSceneNode();

	if (n) {
		n->setMaterialTexture(0, driver->getTexture("/home/xerox/Programmierung/Bibliotheken/irrlicht-1.8.1/media/t351sml.jpg"));
		n->setMaterialFlag(video::EMF_LIGHTING, false);
		scene::ISceneNodeAnimator* anim =
		    smgr->createFlyCircleAnimator(core::vector3df(0,0,50), 30.0f);
		if (anim) {
			n->addAnimator(anim);
			anim->drop();
		}
	}

	scene::IAnimatedMeshSceneNode* anms =
	    smgr->addAnimatedMeshSceneNode(smgr->getMesh("/home/xerox/Programmierung/Bibliotheken/irrlicht-1.8.1/media/ninja.b3d"));

	if (anms) {
		scene::ISceneNodeAnimator* anim =
		    smgr->createFlyStraightAnimator(core::vector3df(100,0,60),
		                                    core::vector3df(-100,200,220), 100000, true);
		if (anim) {
			anms->addAnimator(anim);
			anim->drop();
		}

		anms->setMaterialFlag(video::EMF_LIGHTING, false);

		anms->setFrameLoop(0, 13);
		anms->setAnimationSpeed(15);
//      anms->setMD2Animation(scene::EMAT_RUN);

		anms->setScale(core::vector3df(2.f,2.f,2.f));
		anms->setRotation(core::vector3df(0,-90,0));
//      anms->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"));

	}

	smgr->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(false);

	device->getGUIEnvironment()->addImage(
	    driver->getTexture("/home/xerox/Programmierung/Bibliotheken/irrlicht-1.8.1/media/irrlichtlogoalpha2.tga"),
	    core::position2d<s32>(10,20));

	/*gui::IGUIStaticText* diagnostics = device->getGUIEnvironment()->addStaticText(
	                                       L"", core::rect<s32>(10, 10, 400, 20));
	diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));*/

int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();

	// This is the movemen speed in units per second.
	const f32 MOVEMENT_SPEED = 5.f;

	while(device->run()) {
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		
		core::vector3df nodePosition = node->getPosition();

		if(receiver.isKeyDown(irr::KEY_KEY_W)) {
			if(!receiver.wasKeyDown(irr::KEY_KEY_W)) {
				BOOST_LOG_TRIVIAL(debug)<<"Key deprelled";
			}
		}
		else if(receiver.isKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

		if(receiver.isKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver.isKeyDown(irr::KEY_KEY_D))
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
			
		receiver.update();
		

		node->setPosition(nodePosition);

		driver->beginScene(true, true, video::SColor(255,113,113,133));

		smgr->drawAll(); // draw the 3d scene
		device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

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
