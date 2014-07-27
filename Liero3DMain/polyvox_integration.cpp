#include <irrlicht.h>
#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
#include <PolyVoxCore/MarchingCubesSurfaceExtractor.h>
#include <PolyVoxCore/SurfaceMesh.h>
#include <PolyVoxCore/SimpleVolume.h>
#include <PolyVoxCore/Vector.h>
#include <PolyVoxCore/VertexTypes.h>
#include <PolyVoxCore/Region.h>

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

/*
To be able to use the Irrlicht.DLL file, we need to link with the Irrlicht.lib.
We could set this option in the project settings, but to make it easy, we use a
pragma comment lib for VisualStudio. On Windows platforms, we have to get rid
of the console window, which pops up when starting a program with main(). This
is done by the second pragma. We could also use the WinMain method, though
losing platform independence then.
*/
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "PolyVoxCore.lib")
#endif


irr::scene::IMeshBuffer* convertMesh(const PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal>& mesh) {
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

void createSphereInVolume(SimpleVolume<MaterialDensityPair44>& volData, float fRadius)
{
   //This vector hold the position of the center of the volume
   Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);

   //This three-level for loop iterates over every voxel in the volume
   for (int z = 0; z < volData.getWidth(); z++)
   {
      for (int y = 0; y < volData.getHeight(); y++)
      {
         for (int x = 0; x < volData.getDepth(); x++)
         {
            //Store our current position as a vector...
            Vector3DFloat v3dCurrentPos(x,y,z);
            //And compute how far the current position is from the center of the volume
            float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

            //If the current voxel is less than 'radius' units from the center then we make it solid.
            if(fDistToCenter <= fRadius)
            {
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



void createCuboid(SimpleVolume<MaterialDensityPair44>& volData, Vector3DFloat translation, Vector3DFloat cuboid)
{
   //This three-level for loop iterates over every voxel in the volume
   for (int z = translation.getZ(); z < cuboid.getZ(); z++)
   {
      for (int y = translation.getY(); y < cuboid.getY(); y++)
      {
         for (int x = translation.getX(); x < cuboid.getX(); x++)
         {
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

int main()
{
   IrrlichtDevice *device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 32, false, false, false, 0);

   if (!device)
      return 1;

   /*
   Get a pointer to the VideoDriver, the SceneManager and the graphical
   user interface environment, so that we do not always have to write
   device->getVideoDriver(), device->getSceneManager(), or
   device->getGUIEnvironment().
   */
   IVideoDriver* driver = device->getVideoDriver();
   ISceneManager* smgr = device->getSceneManager();
   IGUIEnvironment* guienv = device->getGUIEnvironment();

   //Create an empty volume and then place a sphere in it
   SimpleVolume<MaterialDensityPair44> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(31, 31, 31)));
   //createSphereInVolume(volData, 10.0F);
   createCuboid(volData,Vector3DFloat(0,0,0), Vector3DFloat(5,10,15));

   SurfaceMesh<PositionMaterialNormal> mesh;

   // Extract the mesh
   PolyVox::MarchingCubesSurfaceExtractor<SimpleVolume<MaterialDensityPair44> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
   surfaceExtractor.execute();

   // Convert the mesh and hand it to Irrlicht
   SMesh* testMesh = new SMesh;
   IMeshBuffer * testBuffer = convertMesh(mesh);
   testMesh->addMeshBuffer(testBuffer);
   testMesh->recalculateBoundingBox();
   ISceneNode* testNode = smgr->addMeshSceneNode(testMesh, 0, 0, vector3df(0, 0, 0), vector3df(0, 0, 0),vector3df(1.0F, 1.0F, 1.0F));
   testNode->setMaterialFlag(video::EMF_LIGHTING, false);

   /*
   To look at the mesh, we place a camera into 3d space
   */

   ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS();


   /*
   Ok, now we have set up the scene, lets draw everything: We run the
   device in a while() loop, until the device does not want to run any
   more. This would be when the user closes the window or presses ALT+F4
   (or whatever keycode closes a window).
   */
   while(device->run())
   {
      /*
      Anything can be drawn between a beginScene() and an endScene()
      call. The beginScene() call clears the screen with a color and
      the depth buffer, if desired. Then we let the Scene Manager and
      the GUI Environment draw their content. With the endScene()
      call everything is presented on the screen.
      */
      driver->beginScene(true, true, SColor(255,100,101,140));

      smgr->drawAll();
      guienv->drawAll();

      driver->endScene();

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