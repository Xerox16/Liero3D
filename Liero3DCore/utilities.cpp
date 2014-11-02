#include <iostream>
#include "exception.h"

#include "utilities.h"

using namespace irr;

IrrlichtDevice* initialize(int width, int height, int fullscreen, IEventReceiver* receiver)
{
	video::E_DRIVER_TYPE driverType;

	std::cout<<
	         "Please select the driver you want for this example:\n"\
	         " (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
	         " (d) Burning's Software Renderer\n (e) Software Renderer\n"\
	         " (f) NullDevice\n (otherKey) exit\n"
	         <<std::endl;

	char i;
	std::cin >> i;

	switch(i) {
	case 'a':
		driverType = video::EDT_OPENGL;
		break;
	case 'b':
		driverType = video::EDT_DIRECT3D9;
		break;
	case 'c':
		driverType = video::EDT_DIRECT3D8;
		break;
	case 'd':
		driverType = video::EDT_BURNINGSVIDEO;
		break;
	case 'e':
		driverType = video::EDT_SOFTWARE;
		break;
	case 'f':
		driverType = video::EDT_NULL;
		break;
	default:
		return NULL;
	}

	//fullscreen set
	bool isFullscreen = ((fullscreen != 0) ? true : false);

	// create device and exit if creation failed

	IrrlichtDevice* device =
	    createDevice(driverType, core::dimension2d<u32>(width, height), 32, isFullscreen, false, false, receiver);
	
	//throw exception if creating irrlicht device failed
	if(!device) {
		BOOST_THROW_EXCEPTION(BasicException("failed to create irrlicht device"));
	}
	
	return device;
}

CConverter::CConverter()
{
   m_wCharBuffer = new wchar_t[1023];
}

CConverter::~CConverter()
{
   delete[] m_wCharBuffer;
}

const wchar_t* CConverter::strToWchart(std::string sInput)
{
   size_t* sizeOut = new size_t;
   size_t sizeInWords = 256;

   const char* cStr;
   cStr = sInput.c_str();
   mbstowcs(m_wCharBuffer, cStr, sizeInWords);
   
   delete sizeOut;
   return m_wCharBuffer;
}

const std::string CConverter::wchartToStr(const wchar_t* wInput)
{
   std::string sOutput = "";
   size_t* nbOfChar = new size_t;
   char* cOut = new char[1023];
   size_t sizeInBytes = 1023;

   wcstombs(cOut,wInput,sizeInBytes); 
   sOutput += cOut;

   delete nbOfChar;
   delete[] cOut;
   return sOutput;

}
