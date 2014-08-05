#include "event_receiver.h"

#include <boost/log/trivial.hpp>

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

void EventReceiver::update() {
	for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
		keysAlreadyDown_[i] = keysDown_[i];
	}
}

bool EventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const {
	return keysDown_[keyCode];
}

bool EventReceiver::wasKeyDown(irr::EKEY_CODE keyCode) const {
	return keysAlreadyDown_[keyCode];
}

void EventReceiver::setKeyDown(irr::EKEY_CODE keyCode, bool state) {
	keysAlreadyDown_[keyCode] = keysDown_[keyCode];
	keysDown_[keyCode] = state;
}
