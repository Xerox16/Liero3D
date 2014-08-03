#ifndef _USER_CONTROLS_H_
#define _USER_CONTROLS_H_

#include <string>
#include <vector>
#include <array>
#include <boost/bimap.hpp>
#include <irrlicht.h>

#include "config.h"
#include "messages.h"
#include "event_receiver.h"

//transforms identifiers of irrlicht keys to their hex representations and vice versa
class Key2String
{
public:
	Key2String(); //initialize key bimap
	irr::EKEY_CODE getKey(const std::string& string_) const;	 //returns the key assigned to the string in the configuration file
	const std::string& getString(irr::EKEY_CODE key) const;	 //returns a constant reference to the name of the key assigned to the integer value

private:
	boost::bimap<std::string, irr::EKEY_CODE> keys_; //a string is associated with a irr::Key
};


class UserControls : public ActionInputSource
{
public:
	enum Action {
	    UP,
	    DOWN,
	    LEFT,
	    RIGHT,
	    ENTER,
	    INVENTORY,
	    MENU,
	    ACTION_COUNT
	};
	static const std::array<std::string, ACTION_COUNT> actions_; //map actions to strings

public:
	void loadProfile(const std::string& profile, const Configuration& configuration, const Key2String& k2s);
	//implement messaging services
	void dispatchEvent(ActionInputListener *listener,  const ActionInputContext &context);
	//raises events of type ActionInputSource if registered keys are down
	void updateInput(EventReceiver& eventReceiver);
	
private:
	std::vector<irr::EKEY_CODE> keys_; //irrlicht hex values for keys of currently loaded profile
};

#endif
