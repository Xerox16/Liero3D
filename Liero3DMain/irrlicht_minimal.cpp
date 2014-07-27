#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

int main() {
	IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1024, 768), 32, false, false, false, 0);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	
	if(!device) {
		return 1;
	}
	
	scene::IMesh* mesh = smgr->getMesh("/home/xerox/Programmierung/C++-Projekte/Irrlicht/Liero3DMain/assets/Cucco/Cucco.3ds");
	if(!mesh) {
		device->drop();
		return 1;
	}
	
	scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	
	scene::ILightSceneNode* light = smgr->add
	
	smgr->addCameraSceneNodeFPS();
	
	while(device->run()) {
		driver->beginScene(true, true, video::SColor(200,140,120,80));
		
		smgr->drawAll();
		
		driver->endScene();
	}
	
	device->drop();
	return 0;
}