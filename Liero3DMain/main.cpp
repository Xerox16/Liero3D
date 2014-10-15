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

scene::IAnimatedMeshSceneNode* ball;

void drawPlayfield(IVideoDriver* driver, scene::ISceneManager* smgr, const Configuration& config) {
	smgr->addSkyBoxSceneNode(
		driver->getTexture(config.getString("skybox.top").c_str()),
		driver->getTexture(config.getString("skybox.bottom").c_str()),
		driver->getTexture(config.getString("skybox.left").c_str()),
		driver->getTexture(config.getString("skybox.right").c_str()),
		driver->getTexture(config.getString("skybox.front").c_str()),
		driver->getTexture(config.getString("skybox.back").c_str())
		);	
	
	ISceneNode* bottom = 0;
	bottom = smgr->addCubeSceneNode(1);
	bottom->setPosition(core::vector3df(0,-12,0));
	bottom->setScale(core::vector3df(110,5,110));
	bottom->setMaterialTexture(0, driver->getTexture(config.getString("textures.bottom").c_str()));
	bottom->setMaterialFlag(video::EMF_LIGHTING, true);
	
		/*
	Sides
	*/
	
    scene::ISceneNode* side = 0;
	
	
	side = smgr->addCubeSceneNode(1);
	side->setPosition(core::vector3df(-52.5,-7,0));
	side->setScale(core::vector3df(5,5,110));
	side->setMaterialTexture(0, driver->getTexture(config.getString("textures.wall").c_str()));
	side->setMaterialFlag(video::EMF_LIGHTING, true);

	side = smgr->addCubeSceneNode(1);
	side->setPosition(core::vector3df(52.5,-7,0));
	side->setScale(core::vector3df(5,5,110));
	side->setMaterialTexture(0, driver->getTexture(config.getString("textures.wall").c_str()));
	side->setMaterialFlag(video::EMF_LIGHTING, true);

	side = smgr->addCubeSceneNode(1);
	side->setPosition(core::vector3df(0,-7,52.5));
	side->setScale(core::vector3df(100,5,5));
	side->setMaterialTexture(0, driver->getTexture(config.getString("textures.wall").c_str()));
	side->setMaterialFlag(video::EMF_LIGHTING, true);
	
	side = smgr->addCubeSceneNode(1);
	side->setPosition(core::vector3df(0,-7,-52.5));
	side->setScale(core::vector3df(100,5,5));
	side->setMaterialTexture(0, driver->getTexture(config.getString("textures.wall").c_str()));
	side->setMaterialFlag(video::EMF_LIGHTING, true);
	
	    // add 2 lights
	bottom = smgr->addLightSceneNode(0, core::vector3df(20,30,40),
		video::SColorf(1.0f, 0.5f, 0.7f, 1.0f), 100.0f);

	bottom = smgr->addLightSceneNode(0, core::vector3df(20,20,-80),
		video::SColorf(1.0f, 0.8f, 0.2f, 1.0f), 200.0f);
		
		//add ball
	IAnimatedMesh* bb = smgr->getMesh(config.getString("meshes.ball").c_str());
	ball = smgr->addAnimatedMeshSceneNode(bb);
	
	ball->setMaterialTexture(0, driver->getTexture(config.getString("textures.ball").c_str()));	
	ball->setScale(core::vector3df(1,1,1));
	ball->setMaterialFlag(video::EMF_LIGHTING, false);
	
}

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
	
	drawPlayfield(driver, sceneManager, config);	
	
	sceneManager->addCameraSceneNodeFPS();
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
				core::stringw str = L"Irrlicht  - Breakout example [";
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
