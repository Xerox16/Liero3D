#include <irrlicht.h>
#include <iostream>
#include <string>
#include <memory>

#include <boost/exception/all.hpp>
#include <boost/test/unit_test.hpp>

#include "utilities.h"
#include "config.h"
#include "exception.h"
#include "event_receiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
	Configuration config;
	IrrlichtDevice* device;
	EventReceiver eventReceiver;

	try {
		config.load("../assets/settings.json");

		int width = config.getInt("general.window_width");
		int height = config.getInt("general.window_height");
		int fullscreen = config.getInt("general.is_fullscreen");

		device = IrrlichtUtilities::initialize(width, height, fullscreen, &eventReceiver);
		if(!device) {
			BOOST_THROW_EXCEPTION(BasicException("aborted creating irrlicht device"));
		}

	} catch(boost::exception& e) {
		std::cout<<boost::diagnostic_information(e)<<std::endl;
		return 1;
	}


	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();
	gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

	device->getFileSystem()->addFileArchive("/home/xerox/Programmierung/Bibliotheken/irrlicht-1.8.1/media/map-20kdm2.pk3");

	scene::IAnimatedMesh* mesh = sceneManager->getMesh("/home/xerox/Programmierung/Bibliotheken/irrlicht-1.8.1/media/20kdm2.bsp");
	scene::ISceneNode* node = NULL;

	if(mesh) {
		node = sceneManager->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	}

	if(node) {
		node->setPosition(core::vector3df(-1300, -144, -1249));
	}

	sceneManager->addCameraSceneNode();
	scene::ICameraSceneNode* root = sceneManager->getActiveCamera();

	device->getCursorControl()->setVisible(true);

	int lastFPS = -1;


	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();

	// This is the movement speed in units per second.
	const f32 MOVEMENT_SPEED = 50.f;

	while(device->run()) {
		if(device->isWindowActive()) {

			// Work out a frame delta time.
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
			then = now;
			
			//move camera according to input
			core::vector3df pos = root->getPosition();
			
			if(eventReceiver.isKeyDown(irr::KEY_KEY_W)) {
				pos.Y += MOVEMENT_SPEED * frameDeltaTime;
			} else if(eventReceiver.isKeyDown(irr::KEY_KEY_S)) {
				pos.Y -= MOVEMENT_SPEED * frameDeltaTime;
			}

			root->setPosition(pos);

			driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
			sceneManager->drawAll();
			driver->endScene();

			int fps = driver->getFPS();


			if(lastFPS != fps) {
				core::stringw str = L"Irrlicht Enige - Quake 3 map example [";
				str += driver->getName();
				str += "] FPS: ";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		} else {
			device->yield();
		}
	}

	device->drop();



	return 0;
};
