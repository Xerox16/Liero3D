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
	
	device->getCursorControl()->setVisible(false);
	
	scene::IMesh* mesh = smgr->getMesh("/home/xerox/Programmierung/C++-Projekte/Irrlicht/Liero3DMain/assets/Cucco/Cucco.3ds");
	if(!mesh) {
		device->drop();
		return 1;
	}
	
	scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	if(node) {
		//node->setMaterialFlag(EMF_LIGHTING, false);
	}
	
   scene::IBillboardSceneNode* billboard = smgr->addBillboardSceneNode(NULL, dimension2d<f32>(32, 32));
   
   billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
   billboard->setMaterialTexture(0, driver->getTexture("/home/xerox/Programmierung/C++-Projekte/Irrlicht/Liero3DMain/assets/Cucco/CuccSS00.tga"));
   billboard->setMaterialFlag(video::EMF_LIGHTING, false);
	
	scene::ILightSceneNode* light = smgr->addLightSceneNode(billboard, core::vector3df(1000,0,0), video::SColorf(1.0f, 0.5f, 1.0f), 800.f);
	
	ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(core::vector3df(0,5,30), 100.0f);
	billboard->addAnimator(anim);
	anim->drop();

	
   ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(NULL, 50.0f, 0.15f);
   
	while(device->run()) {
		driver->beginScene(true, true, video::SColor(255,0,0,0));
		
		smgr->drawAll();
		
		driver->endScene();
	}
	
	device->drop();
	return 0;
}