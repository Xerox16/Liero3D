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

IrrlichtDevice* device;

const int playerCount = 2;
bool gameStarted = false;

scene::IAnimatedMeshSceneNode* ball;
std::vector<scene::IMeshSceneNode*> batters;

gui::IGUIStaticText* status;
gui::IGUIButton* exitButton,* startButton;
scene::ICameraSceneNode* camera;

enum {
	EXIT_GAME = 101,
	START_GAME = 102
};


class MyEventReceiver : public EventReceiver {
public:
	MyEventReceiver() : EventReceiver() {
	}
	
	virtual bool OnEvent(const irr::SEvent& event) {
		EventReceiver::OnEvent(event);
		
		if(!gameStarted) {
			if(event.EventType == EET_GUI_EVENT)
			{
				auto id = event.GUIEvent.Caller->getID();
				switch(event.GUIEvent.EventType) {
					if(id == EXIT_GAME) {
						device->closeDevice();
						return true;
					} else if (id == START_GAME) {
						exitButton->setVisible(false);
						startButton->setVisible(false);	
                    // static camera
						camera->removeAnimators();
						camera->setTarget(core::vector3df(0,-20,0));
						camera->setPosition(core::vector3df(10,50,-90));				
					}
				}
			}
		}
		return false;
	}
};

void drawPlayfield(IVideoDriver* driver, scene::ISceneManager* smgr, const Configuration& config) {
	/*smgr->addSkyBoxSceneNode(
		driver->getTexture(config.getString("textures.skybox_top").c_str()),
		driver->getTexture(config.getString("textures.skybox_bottom").c_str()),
		driver->getTexture(config.getString("textures.skybox_left").c_str()),
		driver->getTexture(config.getString("textures.skybox_right").c_str()),
		driver->getTexture(config.getString("textures.skybox_front").c_str()),
		driver->getTexture(config.getString("textures.skybox_back").c_str())
		);	*/
		
	smgr->addSkyDomeSceneNode(driver->getTexture(config.getString("textures.skydome").c_str()));	
	
	//bottom 
	
	ISceneNode* bottom = 0;
	bottom = smgr->addCubeSceneNode(1);
	bottom->setPosition(core::vector3df(0,-12,0));
	bottom->setScale(core::vector3df(110,5,110));
	bottom->setMaterialTexture(0, driver->getTexture(config.getString("textures.bottom").c_str()));
	bottom->setMaterialFlag(video::EMF_LIGHTING, true);
	
	//sides
	
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
	
	    // add 2 lights
	bottom = smgr->addLightSceneNode(0, core::vector3df(20,30,40),
		video::SColorf(1.0f, 0.5f, 0.7f, 1.0f), 100.0f);

	bottom = smgr->addLightSceneNode(0, core::vector3df(20,20,-80),
		video::SColorf(1.0f, 0.8f, 0.2f, 1.0f), 200.0f);
		
		//add ball
	IAnimatedMesh* bb = smgr->getMesh(config.getString("meshes.ball").c_str());
	ball = smgr->addAnimatedMeshSceneNode(bb);
	
	ball->setPosition(vector3df(0, -7, 0));
	ball->setMaterialTexture(0, driver->getTexture(config.getString("textures.ball").c_str()));	
	ball->setScale(core::vector3df(1,1,1));
	ball->setMaterialFlag(video::EMF_LIGHTING, false);
	
	ISceneNodeAnimator* anim = smgr->createRotationAnimator(vector3df(2.0, 53, 1.0));
	ball->addAnimator(anim);
	
	for(int i = 0; i < playerCount; ++i) {
		batters.push_back(smgr->addCubeSceneNode(10));
	
		batters[i]->setPosition(vector3df(0, -7, i == 0 ? -52.5 : 52.5));
		batters[i]->setMaterialTexture(0, driver->getTexture(config.getString("textures.batter").c_str()));
		batters[i]->setScale(vector3df(1.5, 0.5, 0.2));
		batters[i]->setMaterialFlag(video::EMF_LIGHTING, true);
	}
	
	
}

void menu(IrrlichtDevice* device, video::IVideoDriver* driver, gui::IGUIEnvironment* env, scene::ISceneManager* smgr, const Configuration& config, scene::ICameraSceneNode* camera) {
	
	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont(config.getString("fonts.menu").c_str());
	if (font)
		skin->setFont(font);

	skin->setColor(EGDC_BUTTON_TEXT,video::SColor(255,255,220,100));

	//env->addImage(driver->getTexture(config.getString("images.logo").c_str()), core::position2d<s32>(5,5));
	
	int width = 450;
	int height = 60;
	dimension2d<u32> size = device->getVideoDriver()->getScreenSize();
	rect<int> pos(10, size.Height - height, 10 + width, size.Height - 10);
	env->addImage(pos);
	
	status = env->addStaticText(L"Irrlicht WOS 06 Demo", pos, true,false);
	status->setOverrideColor(video::SColor(255,205,200,200));
	
	device->getCursorControl()->setVisible(true);
	
	int halfScreenWidth = driver->getScreenSize().Width / 2;
	
	startButton = env->addButton(rect<s32>(halfScreenWidth-100,210,halfScreenWidth+100,250), 0, START_GAME, L"New Game");
	exitButton  = env->addButton(rect<s32>(halfScreenWidth-100,290,halfScreenWidth+100,330), 0, EXIT_GAME, L"Quit");

	
	camera = smgr->addCameraSceneNode();
	camera->setTarget(vector3df(0,0,0));
	auto anim = smgr->createFlyCircleAnimator(vector3df(0, 30, -100), 30.0f);
	camera->addAnimator(anim);
}

int main()
{
	Configuration config;
	MyEventReceiver eventReceiver;

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
	menu(device, driver, guiEnvironment, sceneManager, config, camera);
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
			/*
			//move camera according to input
			core::vector3df pos = root->getPosition();
			
			if(eventReceiver.isKeyDown(irr::KEY_KEY_W)) {
				pos.Y += MOVEMENT_SPEED * frameDeltaTime;
			} else if(eventReceiver.isKeyDown(irr::KEY_KEY_S)) {
				pos.Y -= MOVEMENT_SPEED * frameDeltaTime;
			}

			root->setPosition(pos);*/

			driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
			sceneManager->drawAll();
			guiEnvironment->drawAll();
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
