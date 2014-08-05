#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <irrlicht.h>
#include <array>

class EventReceiver : public irr::IEventReceiver {
public:
//initialize members
	EventReceiver();


	void update();
//handle keyboard events
	virtual bool OnEvent(const irr::SEvent& event);
//return if key is down
	virtual bool isKeyDown(irr::EKEY_CODE keyCode) const;
//return if key was down when the function was called the last time
	virtual bool wasKeyDown(irr::EKEY_CODE keyCode) const;
	
//DEBUGGING FUNCTIONS
//set key state manually for testing
	virtual void setKeyDown(irr::EKEY_CODE keyCode, bool state = true);
	
private:
	std::array<bool, irr::KEY_KEY_CODES_COUNT> keysDown_;
	std::array<bool, irr::KEY_KEY_CODES_COUNT> keysAlreadyDown_;
};


#endif