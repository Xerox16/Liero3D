#include <irrlicht.h>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>

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

struct IrrlichtHelper {
	IrrlichtDevice* device;	//irrlicht main device
	video::IVideoDriver* driver; //video driver
	scene::ISceneManager* smgr; //scene manager
	gui::IGUIEnvironment* gui; //gui
};

enum {
	QUIT_GAME = 101,
	START_GAME = 102
};

int playerCount = 2;
bool gameStarted = false;

scene::IAnimatedMeshSceneNode* ball;
scene::ISceneNodeAnimator* ballAnim;
f32 ballSpeedX = 20.f;
f32 ballSpeedY = 20.f;

scene::ICameraSceneNode* camera;
scene::ISceneNodeAnimator* camAnim;

std::vector<scene::IMeshSceneNode*> batters;
f32 batterSpeed = 50.f;

gui::IGUIStaticText* status;
gui::IGUIButton* exitButton,* startButton;


//create pong event receiver
class MyEventReceiver : public EventReceiver
{
public:
	MyEventReceiver() : EventReceiver(), irrH_() {
	}

	virtual bool OnEvent(const irr::SEvent& event) {
		EventReceiver::OnEvent(event);

//if game has not yet started
		if (!gameStarted) {
			//check for gui events
			if (event.EventType == EET_GUI_EVENT) {
				//get event id
				s32 id = event.GUIEvent.Caller->getID();
				switch(event.GUIEvent.EventType) {
					//if button is clicked check event id
				case EGET_BUTTON_CLICKED:
					if (id == QUIT_GAME) {
						irrH_.device->closeDevice();
						return true;
					}
					if (id == START_GAME) {
						exitButton->setVisible(false);
						startButton->setVisible(false);
						// remove camera animator
						camera->removeAnimator(camAnim);
						//set new camera position
						camera->setTarget(core::vector3df(0,-20,0));
						camera->setPosition(core::vector3df(10,50,-90));

						ball->setPosition(vector3df(0, -9, -45));
						ball->removeAnimator(ballAnim);

						//render cursor invisible
						irrH_.device->getCursorControl()->setVisible(false);
						//indicate that game starts
						gameStarted = true;
					}
				}
			}

			return false;
		} else {
			return false;
		}
	}

	void setIrrlichtHelper(IrrlichtHelper irrH) {
		irrH_ = irrH;
	}

private:
	IrrlichtHelper irrH_;
};

void drawPlayfield(IrrlichtHelper irrH, const Configuration& config)
{
	//add skydome
	irrH.smgr->addSkyDomeSceneNode(irrH.driver->getTexture(config.getString("textures.skydome").c_str()));

	//add game borders

	//bottom
	ISceneNode* bottom = 0;
	bottom = irrH.smgr->addCubeSceneNode(1);
	bottom->setPosition(core::vector3df(0,-12,0));
	bottom->setScale(core::vector3df(110,5,110));
	bottom->setMaterialTexture(0, irrH.driver->getTexture(config.getString("textures.bottom").c_str()));
	bottom->setMaterialFlag(video::EMF_LIGHTING, true);

	//sides
	scene::ISceneNode* side = 0;

	side = irrH.smgr->addCubeSceneNode(1);
	side->setPosition(core::vector3df(-52.5,-7,0));
	side->setScale(core::vector3df(5,5,110));
	side->setMaterialTexture(0, irrH.driver->getTexture(config.getString("textures.wall").c_str()));
	side->setMaterialFlag(video::EMF_LIGHTING, true);

	side = irrH.smgr->addCubeSceneNode(1);
	side->setPosition(core::vector3df(52.5,-7,0));
	side->setScale(core::vector3df(5,5,110));
	side->setMaterialTexture(0, irrH.driver->getTexture(config.getString("textures.wall").c_str()));
	side->setMaterialFlag(video::EMF_LIGHTING, true);

	// add 2 lights to illuminate game board
	bottom = irrH.smgr->addLightSceneNode(0, core::vector3df(20,30,40),
	                                      video::SColorf(1.0f, 0.5f, 0.7f, 1.0f), 100.0f);

	bottom = irrH.smgr->addLightSceneNode(0, core::vector3df(20,20,-80),
	                                      video::SColorf(1.0f, 0.8f, 0.2f, 1.0f), 200.0f);

	//add ball
	//load animated mesh
	IAnimatedMesh* bb = irrH.smgr->getMesh(config.getString("meshes.ball").c_str());
	ball = irrH.smgr->addAnimatedMeshSceneNode(bb);

	ball->setPosition(vector3df(0, -7, 0));
	ball->setMaterialTexture(0, irrH.driver->getTexture(config.getString("textures.ball").c_str()));
	ball->setScale(core::vector3df(1,1,1));
	ball->setMaterialFlag(video::EMF_LIGHTING, false);

	//let ball rotate
	ballAnim = irrH.smgr->createRotationAnimator(vector3df(2.0, 53, 1.0));
	ball->addAnimator(ballAnim);

	//add two batters
	batters.push_back(irrH.smgr->addCubeSceneNode(10));

	batters[0]->setPosition(vector3df(0, -7, -52.5));
	batters[0]->setMaterialTexture(0, irrH.driver->getTexture(config.getString("textures.batter").c_str()));
	batters[0]->setScale(vector3df(1.5, 0.5, 0.2));
	batters[0]->setMaterialFlag(video::EMF_LIGHTING, true);
	
	batters.push_back(irrH.smgr->addCubeSceneNode(10));

	batters[1]->setPosition(vector3df(0, -7, 52.5));
	batters[1]->setMaterialTexture(0, irrH.driver->getTexture(config.getString("textures.batter").c_str()));
	batters[1]->setScale(vector3df(1.5, 0.5, 0.2));
	batters[1]->setMaterialFlag(video::EMF_LIGHTING, true);

}

void menu(IrrlichtHelper irrH, const Configuration& config)
{

	//get gui skin and set font
	IGUISkin* skin = irrH.gui->getSkin();
	IGUIFont* font = irrH.gui->getFont(config.getString("fonts.menu").c_str());
	if (font) {
		skin->setFont(font);
	}
	
	skin->setColor(EGDC_BUTTON_TEXT,video::SColor(255,255,220,100));

	//add game logo
	irrH.gui->addImage(irrH.driver->getTexture(config.getString("images.logo").c_str()), core::position2d<s32>(5,5));

	int width = 450;
	int height = 60;
	dimension2d<u32> size = irrH.device->getVideoDriver()->getScreenSize();
	rect<int> pos(10, size.Height - height, 10 + width, size.Height - 10);
	irrH.gui->addImage(pos);

	//add static stext
	status = irrH.gui->addStaticText(L"Irrlicht WOS 06 Demo", pos, true,false);
	status->setOverrideColor(video::SColor(255,205,200,200));

	//rencer cursor visible
	irrH.device->getCursorControl()->setVisible(true);

	//show menu buttons at correct position
	int halfScreenWidth = irrH.driver->getScreenSize().Width / 2;

	startButton = irrH.gui->addButton(rect<s32>(halfScreenWidth-100,210,halfScreenWidth+100,250), 0, START_GAME, L"New Game");
	exitButton  = irrH.gui->addButton(rect<s32>(halfScreenWidth-100,290,halfScreenWidth+100,330), 0, QUIT_GAME, L"Quit");

	//add camera
	camera = irrH.smgr->addCameraSceneNode();
	camera->setTarget(vector3df(0,0,0));
	camAnim = irrH.smgr->createFlyCircleAnimator(vector3df(0, 30, -100), 30.0f);
	camera->addAnimator(camAnim);
}

int main()
{
	IrrlichtDevice* device;

	Configuration config;
	//create irrlicht helper to simplify passing irrlicht objects around
	IrrlichtHelper irrH;
	//create event receiver
	MyEventReceiver eventReceiver;

	//load configuration from file
	try {
		config.load("../assets/settings.json");

		int width = config.getInt("general.window_width");

		int height = config.getInt("general.window_height");
		int fullscreen = config.getInt("general.is_fullscreen");

		device = IrrlichtUtilities::initialize(width, height, fullscreen, &eventReceiver);

		//handle exception in case creation of irrlicht device fails
	} catch(boost::exception& e) {
		std::cout<<boost::diagnostic_information(e)<<std::endl;
		return 1;
	}

	irrH.device = device;
	irrH.driver = device->getVideoDriver();
	irrH.smgr = device->getSceneManager();
	irrH.gui = device->getGUIEnvironment();

	eventReceiver.setIrrlichtHelper(irrH);

	//create converter from irrlicht strings to normal strings and back
	IrrlichtUtilities::CConverter converter;

	//create pong field
	drawPlayfield(irrH, config);

	//show menu
	menu(irrH, config);

	//integer to track fps
	int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();

	while(device->run()) {
		if(device->isWindowActive()) {
			
			//show game information
			if(gameStarted) {
				std::ostringstream statusText;
				statusText<<"Level: "<< 0 <<" Balls: "<< 0;
				status->setText(converter.strToWchart(statusText.str()));
			}

			// Work out a frame delta time.
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
			then = now;

			
			//move ball
			core::vector3df pos = ball->getPosition();
			
			pos.X += ballSpeedX * frameDeltaTime;
			pos.Y += ballSpeedY * frameDeltaTime;

			ball->setPosition(pos);

			irrH.driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
			irrH.smgr->drawAll();
			irrH.gui->drawAll();
			irrH.driver->endScene();


			int fps = irrH.driver->getFPS();

			if (lastFPS != fps) {
				core::stringw tmp(L"Movement Example - Irrlicht Engine [");
				tmp += irrH.driver->getName();
				tmp += L"] fps: ";
				tmp += fps;

				irrH.device->setWindowCaption(tmp.c_str());
				lastFPS = fps;
			}
		}
	}

	irrH.device->drop();

	return 0;
};
