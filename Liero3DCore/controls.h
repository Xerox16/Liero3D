#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <string>
#include <vector>
#include <array>

#include <boost/bimap.hpp>

#include "constants.h"

class ControlKeyTranslation {
public:
	ControlKeyTranslation(); //initialize key bimap
	const std::string& getButton(int value) const;	 //returns a constant reference to the name of the key assigned to the integer value
	
private:
    boost::bimap<std::string, int> keys_; //a string is associated with a irr::Key
}

class PlayerControls {
public:
    PlayerControls(); //current configuration file MUST contain controls, otherwhise default controls are loaded
    virtual ~PlayerControls();

    void fillKeyArray(); //NOTE: This function must be used before any of the functions below are used
    bool getKey(size_t player,Joypad::BUTTON) const;
    bool getDeprelledKey(size_t player,Joypad::BUTTON);

    void setButton(size_t player,Joypad::BUTTON, int value);
    const std::string& getButton(int value) const;	 //returns a constant reference to the name of the key assigned to the integer value
    const std::string& getButton(size_t player,Joypad::BUTTON) const;	 //returns a constant reference to the name of the key assigned to the direction

private:
    static const std::array<std::string,PLAYER_COUNT> playerIDs_;
    static const std::array<std::string,Joypad::BUTTON_COUNT> directionIDs_;

    //fills the control map with valid values
    void fillControlMap();

    void loadDefaultButtons(); //load default controls
    void loadButtons(); //loads controls from current config file


    std::array<bool,Joypad::BUTTON_COUNT * PLAYER_COUNT> pressedKeys_; //stores which keys are pressed for deprelling
    std::vector< std::shared_ptr<Joypad> > joysticks_;
};



#endif