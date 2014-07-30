#include "event_receiver.h"

EventReceiver::EventReceiver() : keysDown_() {
	for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
		keysDown_[i] = false;
		keysAlreadyDown_[i] = false;
	}
}

bool EventReceiver::OnEvent(const irr::SEvent& event) {
	//register for keyboard events
	if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
		keysDown_[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
		
	return false;
}
	
bool EventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const {
	return keysDown_[keyCode];
}

bool EventReceiver::wasKeyDown(irr::EKEY_CODE keyCode) {
	bool wasDown = keysAlreadyDown_[keyCode];
	
	if(keysDown_[keyCode]) {
		//else check if it is pressed right now and set keys that were down accordingly
		keysAlreadyDown_[keyCode] = true;
	} else {
		keysAlreadyDown_[keyCode] = false;
	}
		
	return wasDown;
}

void EventReceiver::setKeyDown(irr::EKEY_CODE keyCode, bool state) {
	keysDown_[keyCode] = state;
}
