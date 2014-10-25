#include <irrlicht.h>

#include <irrlicht.h>
#include <iostream>
#include <string>
#include <memory>

#include <boost/exception/all.hpp>
#include <boost/test/unit_test.hpp>

#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
#include <PolyVoxCore/MarchingCubesSurfaceExtractor.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/SimpleVolume.h>
#include <PolyVoxCore/Vector.h>
#include <PolyVoxCore/VertexTypes.h>
#include <PolyVoxCore/Region.h>

#include "utilities.h"
#include "config.h"
#include "exception.h"
#include "event_receiver.h"


/*
In the Irrlicht Engine, everything can be found in the namespace 'irr'. So if
you want to use a class of the engine, you have to write irr:: before the name
of the class. For example to use the IrrlichtDevice write: irr::IrrlichtDevice.
To get rid of the irr:: in front of the name of every class, we tell the
compiler that we use that namespace from now on, and we will not have to write
irr:: anymore.
*/
using namespace irr;

using namespace PolyVox;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look at them, you can
read a detailed description of them in the documentation by clicking on the top
menu item 'Namespace List' or by using this link:
http://irrlicht.sourceforge.net/docu/namespaces.html
Like the irr namespace, we do not want these 5 sub namespaces now, to keep this
example simple. Hence, we tell the compiler again that we do not want always to
write their names.
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;


irr::scene::IMeshBuffer* convertMesh(const PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal>& mesh)
{
	const std::vector<uint32_t>& indices = mesh.getIndices();
	const std::vector<PolyVox::PositionMaterialNormal>& vertices = mesh.getVertices();

	irr::scene::IDynamicMeshBuffer *mb = new irr::scene::CDynamicMeshBuffer(irr::video::EVT_STANDARD, irr::video::EIT_32BIT);
	mb->getVertexBuffer().set_used(vertices.size());
	// This loop doesn't seem to be executed at all... in other words, vertices.size() == 0
	for (size_t i = 0; i < vertices.size(); ++i) {
		const PolyVox::Vector3DFloat& position = vertices[i].getPosition();
		const PolyVox::Vector3DFloat& normal = vertices[i].getNormal();
		mb->getVertexBuffer()[i].Pos.X = position.getX();
		mb->getVertexBuffer()[i].Pos.Y = position.getY();
		mb->getVertexBuffer()[i].Pos.Z = position.getZ();
		mb->getVertexBuffer()[i].Normal.X = normal.getX();
		mb->getVertexBuffer()[i].Normal.Y = normal.getY();
		mb->getVertexBuffer()[i].Normal.Z = normal.getZ();
		// Cubes should show up in bright green
		mb->getVertexBuffer()[i].Color = irr::video::SColor(255,0,255,0);
	}
	mb->getIndexBuffer().set_used(indices.size());
	for (size_t i = 0; i < indices.size(); ++i) {
		mb->getIndexBuffer().setValue(i, indices[i]);
	}
	mb->recalculateBoundingBox();
	return mb;
}

void createSphereInVolume(SimpleVolume<MaterialDensityPair44>& volData, Vector3DFloat translation, float fRadius)
{
	//This vector hold the position of the center of the volume
	Vector3DFloat v3dVolCenter(translation);

	//This three-level for loop iterates over every voxel in the volume
	for (int z = 0; z < volData.getWidth(); z++) {
		for (int y = 0; y < volData.getHeight(); y++) {
			for (int x = 0; x < volData.getDepth(); x++) {
				//Store our current position as a vector...
				Vector3DFloat v3dCurrentPos(x,y,z);
				//And compute how far the current position is from the center of the volume
				float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

				//If the current voxel is less than 'radius' units from the center then we make it solid.
				if(fDistToCenter <= fRadius) {
					// This portion seems to be working correctly
					//Our new density value
					uint8_t uDensity = MaterialDensityPair44::getMaxDensity();

					//Get the old voxel
					MaterialDensityPair44 voxel = volData.getVoxelAt(x,y,z);

					//Modify the density
					voxel.setDensity(uDensity);

					//Modify the material
					voxel.setMaterial(1); //        <-- Add this line

					//Wrte the voxel value into the volume
					volData.setVoxelAt(x, y, z, voxel);
				}
			}
		}
	}
}



void createCuboid(SimpleVolume<MaterialDensityPair44>& volData, Vector3DFloat translation, Vector3DFloat size)
{
	
	//This three-level for loop iterates over every voxel in the volume
	for (int z = translation.getZ(); z < size.getZ(); z++) {
		for (int y = translation.getY(); y < size.getY(); y++) {
			for (int x = translation.getX(); x < size.getX(); x++) {
				// This portion seems to be working correctly
				//Our new density value
				uint8_t uDensity = MaterialDensityPair44::getMaxDensity();

				//Get the old voxel
				MaterialDensityPair44 voxel = volData.getVoxelAt(x,y,z);

				//Modify the density
				voxel.setDensity(uDensity);

				//Modify the material
				voxel.setMaterial(1); 

				//Write the voxel value into the volume
				volData.setVoxelAt(x, y, z, voxel);
			}
		}
	}
}

void fillVolume(SimpleVolume<MaterialDensityPair44>& volData)
{
	
	//This three-level for loop iterates over every voxel in the volume
	for (int z = 3; z < volData.getHeight() - 3; z++) {
		for (int y = 3; y < volData.getDepth() - 3; y++) {
			for (int x = 3; x < volData.getWidth() - 3; x++) {
				// This portion seems to be working correctly
				//Our new density value
				uint8_t uDensity = MaterialDensityPair44::getMaxDensity();

				//Get the old voxel
				MaterialDensityPair44 voxel = volData.getVoxelAt(x,y,z);

				//Modify the density
				voxel.setDensity(uDensity);

				//Modify the material
				voxel.setMaterial(1); 

				//Write the voxel value into the volume
				volData.setVoxelAt(x, y, z, voxel);
			}
		}
	}
}

int main()
{
	Configuration config;
	IrrlichtDevice* device;
	EventReceiver eventReceiver;

	try {
		config.load("../assets/settings.json");

		int width = config.getInt("general.window_width");

		int height = config.getInt("general.window_height")
		;
		int fullscreen = config.getInt("general.is_fullscreen");

		device = IrrlichtUtilities::initialize(width, height, fullscreen, &eventReceiver);
		if(!device) {
			BOOST_THROW_EXCEPTION(BasicException("aborted creating irrlicht device"));
		}

	} catch(boost::exception& e) {
		std::cout<<boost::diagnostic_information(e)<<std::endl;
		return 1;
	}
	
	//do not show cursor
	device->getCursorControl()->setVisible(false);

	/*
	Get a pointer to the VideoDriver, the SceneManager and the graphical
	user interface environment, so that we do not always have to write
	device->getVideoDriver(), device->getSceneManager(), or
	device->getGUIEnvironment().
	*/
	IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	
	smgr->addSkyBoxSceneNode(
		driver->getTexture(config.getString("skybox.top").c_str()),
		driver->getTexture(config.getString("skybox.bottom").c_str()),
		driver->getTexture(config.getString("skybox.left").c_str()),
		driver->getTexture(config.getString("skybox.right").c_str()),
		driver->getTexture(config.getString("skybox.front").c_str()),
		driver->getTexture(config.getString("skybox.back").c_str())
	);	
	
	//bottom 
	
	ISceneNode* bottom = 0;
	bottom = smgr->addCubeSceneNode(1);
	bottom->setPosition(core::vector3df(31.5,0,31.5));
	bottom->setScale(core::vector3df(63,1,63));
	bottom->setMaterialTexture(0, driver->getTexture(config.getString("textures.bottom").c_str()));
	bottom->setMaterialFlag(video::EMF_LIGHTING, false);

	//Create an empty volume and then place a sphere in it
	SimpleVolume<MaterialDensityPair44> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(63, 63, 63)));
	fillVolume(volData);

	SurfaceMesh<PositionMaterialNormal> mesh;

	// Extract the mesh
	PolyVox::MarchingCubesSurfaceExtractor<SimpleVolume<MaterialDensityPair44> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
	surfaceExtractor.execute();

	// Convert the mesh and hand it to Irrlicht
	scene::SMesh* testMesh = new SMesh;
	IMeshBuffer * testBuffer = convertMesh(mesh);
	testMesh->addMeshBuffer(testBuffer);
	testMesh->recalculateBoundingBox();
	

	ISceneNode* meshNode = smgr->addMeshSceneNode(testMesh);
	meshNode->setMaterialFlag(video::EMF_LIGHTING, false);

/*
	// create light
	ISceneNode* node = smgr->addLightSceneNode(0, core::vector3df(0,0,0), video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
	if(node) {
		scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator (core::vector3df(0,150,0),250.0f);
		node->addAnimator(anim);
		anim->drop();

		// attach billboard to light
		node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
		if(node) {
			node->setMaterialFlag(video::EMF_LIGHTING, false);
			node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			node->setMaterialTexture(0, driver->getTexture(config.getString("textures.bottom").c_str()));
		}
	}*/



	/*
	To look at the mesh, we place a camera into 3d space
	*/

	smgr->addCameraSceneNodeFPS();
	
	int lastFPS = -1;
	
	int then = device->getTimer()->getTime();
	
	const float MOVEMENT_SPEED = 5.0;
	
	/*
	Ok, now we have set up the scene, lets draw everything: We run the
	device in a while() loop, until the device does not want to run any
	more. This would be when the user closes the window or presses ALT+F4
	(or whatever keycode closes a window).
	*/
	int primitivesDrawnLast = -1;
	int updateMeshCounter = 0;
	int changeWorldCounter = 0;	
	int i = 0;
	
	while(device->run()) {
		const int now = device->getTimer()->getTime();
		const float frameDeltaTime = static_cast<float> (now - then) / 1000.0;
		then = now;
		
		/*
		Anything can be drawn between a beginScene() and an endScene()
		call. The beginScene() call clears the screen with a color and
		the depth buffer, if desired. Then we let the Scene Manager and
		the GUI Environment draw their content. With the endScene()
		call everything is presented on the screen.
		*/
		driver->beginScene(true, true, SColor(255,0,0,0));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
		
		if(changeWorldCounter++ == 1) {
			createSphereInVolume(volData, Vector3DFloat(i,i,i), (float)i);
			changeWorldCounter = 0;
			i++;
		}
		
		if(updateMeshCounter++ == 1) {
			
			
			//delete old mesh
			testMesh->clear();
			
			//extract altered mesh
			PolyVox::MarchingCubesSurfaceExtractor<SimpleVolume<MaterialDensityPair44> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
			surfaceExtractor.execute();

			//convert mesh and hand it to irrlicht
			IMeshBuffer * testBuffer = convertMesh(mesh);
			testMesh->clear();
			testMesh->addMeshBuffer(testBuffer);
			testMesh->recalculateBoundingBox();
			
			updateMeshCounter = 0;
		}
				
		int primitivesDrawn = driver->getPrimitiveCountDrawn();
		int fps = driver->getFPS();
		
	
		if(primitivesDrawn != primitivesDrawnLast || lastFPS != fps) {
			stringw str = L"IrrlichtExample [Primitives Drawn: ";
			str += primitivesDrawn;
			str += "]  [";
			str += driver->getName();
			str += "] FPS: ";
			str += fps;
			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}

	}

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/
	device->drop();

	return 0;
}
