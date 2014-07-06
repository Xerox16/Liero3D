#include <irrlicht.h>
#include <iostream>
#include <string>
#include <memory>

#include <boost/exception/all.hpp> 
#include <boost/test/unit_test.hpp>

#include "header/utilities.h"
#include "header/config.h"

using namespace irr;



const int widht = 640;
const int height = 480;

int main()
{
	Configuration config;
	
	try {
	config.load("/home/xerox/Programmierung/Projekte/Liero3D/assets/settings.json");
	} catch(boost::exception& e) {
		std::cout<<boost::diagnostic_information(e)<<std::endl;
		return 2;
	}
	IrrlichtDevice* device = IrrlichtUtilities::initialize(widht, height);	
	if(device == 0) {
		return 1;
	}
	
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();
	device->getFileSystem()->addFileArchive("/home/xerox/Programmierung/Projekte/Irllicht/media/map-20kdm2.pk3");
	
	scene::IAnimatedMesh* mesh = sceneManager->getMesh("/home/xerox/Programmierung/Projekte/Irllicht/media/20kdm2.bsp");
	scene::ISceneNode* node = NULL;
	
	if(mesh) {
		node = sceneManager->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	}
	
	if(node) {
		node->setPosition(core::vector3df(-1300, -144, -1249));
	}
	
	sceneManager->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(true);
	
	int lastFPS = -1;
	
	while(device->run()) {
		if(device->isWindowActive()) {
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
