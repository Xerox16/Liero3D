#include <irrlicht.h>
#include <iostream>
#include <string>
#include <memory>

#include <boost/exception/all.hpp> 
#include <boost/test/unit_test.hpp>

#include "header/utilities.h"
#include "header/config.h"
#include "header/exception.h"

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
	
	try {
	config.load("/home/xerox/Programmierung/Projekte/Liero3D/assets/settings.json");
	
	int width = config.getInt("general.window_width");
	int height = config.getInt("general.window_height");
	int fullscreen = config.getInt("general.is_fullscreen");
	
	device = IrrlichtUtilities::initialize(width, height, fullscreen);	
	if(!device) {
		BOOST_THROW_EXCEPTION(BasicException("Failed to create Irrlicht device"));
	}
	
	} catch(boost::exception& e) {
		std::cout<<boost::diagnostic_information(e)<<std::endl;
		return 1;
	}
	
	
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();
	gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();
	
	device->getFileSystem()->addFileArchive("/home/xerox/Programmierung/Projekte/Irllicht/media/map-20kdm2.pk3");
	
	scene::IAnimatedMesh* mesh = sceneManager->getMesh("/home/xerox/Programmierung/Projekte/Irllicht/media/20kdm2.bsp");
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
	
	core::vector3df pos(1.0,0.0,0.0);
	
	while(device->run()) {
		if(device->isWindowActive()) {
		
		pos = core::vector3df(pos.X  - 0.001, pos.Y, pos.Z - 0.001);
		
		root->setTarget(pos);
		
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
