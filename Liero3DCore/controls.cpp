#include "controls.h"

#include <boost/log/trivial.hpp>

#include "config.h"
#include "exception.h"



ControlKeyTranslation::ControlKeyTranslation()
	:keys_()
{
	typedef boost::bimap<std::string,int> bimap;
	typedef bimap::value_type value_pair;
	irr::KEY_KEY_0
	std::vector<value_pair> v = {
		{"KEY_LBUTTON", KEY_LBUTTON}, // Left mouse button
		{"KEY_RBUTTON", KEY_RBUTTON}, // Right mouse button
		{"KEY_CANCEL", KEY_CANCEL}, // Control-break processing
		{"KEY_MBUTTON", KEY_MBUTTON}, // Middle mouse button (three-button mouse)
		{"KEY_XBUTTON1", KEY_XBUTTON1}, // Windows 2000/XP: X1 mouse button
		{"KEY_XBUTTON2", KEY_XBUTTON2}, // Windows 2000/XP: X2 mouse button
		{"KEY_BACK", KEY_BACK}, // BACKSPACE key
		{"KEY_TAB", KEY_TAB}, // TAB key
		{"KEY_CLEAR", KEY_CLEAR}, // CLEAR key
		{"KEY_RETURN", KEY_RETURN}, // ENTER key
		{"KEY_SHIFT", KEY_SHIFT}, // SHIFT key
		{"KEY_CONTROL", KEY_CONTROL}, // CTRL key
		{"KEY_MENU", KEY_MENU}, // ALT key
		{"KEY_PAUSE", KEY_PAUSE}, // PAUSE key
		{"KEY_CAPITAL", KEY_CAPITAL}, // CAPS LOCK key
		{"KEY_KANA", KEY_KANA}, // IME Kana mode
		{"KEY_HANGUEL", KEY_HANGUEL}, // IME Hanguel mode (maintained for compatibility use KEY_HANGUL)
		{"KEY_HANGUL", KEY_HANGUL}, // IME Hangul mode
		{"KEY_JUNJA", KEY_JUNJA}, // IME Junja mode
		{"KEY_FINAL", KEY_FINAL}, // IME final mode
		{"KEY_HANJA", KEY_HANJA}, // IME Hanja mode
		{"KEY_KANJI", KEY_KANJI}, // IME Kanji mode
		{"KEY_ESCAPE", KEY_ESCAPE}, // ESC key
		{"KEY_CONVERT", KEY_CONVERT}, // IME convert
		{"KEY_NONCONVERT", KEY_NONCONVERT}, // IME nonconvert
		{"KEY_ACCEPT", KEY_ACCEPT}, // IME accept
		{"KEY_MODECHANGE", KEY_MODECHANGE}, // IME mode change request
		{"KEY_SPACE", KEY_SPACE}, // SPACEBAR
		{"KEY_PRIOR", KEY_PRIOR}, // PAGE UP key
		{"KEY_NEXT", KEY_NEXT}, // PAGE DOWN key
		{"KEY_END", KEY_END}, // END key
		{"KEY_HOME", KEY_HOME}, // HOME key
		{"KEY_LEFT", KEY_LEFT}, // LEFT ARROW key
		{"KEY_UP", KEY_UP}, // UP ARROW key
		{"KEY_RIGHT", KEY_RIGHT}, // RIGHT ARROW key
		{"KEY_DOWN", KEY_DOWN}, // DOWN ARROW key
		{"KEY_SELECT", KEY_SELECT}, // SELECT key
		{"KEY_PRINT", KEY_PRINT}, // PRINT key
		{"KEY_EXECUT", KEY_EXECUT}, // EXECUTE key
		{"KEY_SNAPSHOT", KEY_SNAPSHOT}, // PRINT SCREEN key
		{"KEY_INSERT", KEY_INSERT}, // INS key
		{"KEY_DELETE", KEY_DELETE}, // DEL key
		{"KEY_HELP", KEY_HELP}, // HELP key
		{"KEY_KEY_0", KEY_KEY_0}, // 0 key
		{"KEY_KEY_1", KEY_KEY_1}, // 1 key
		{"KEY_KEY_2", KEY_KEY_2}, // 2 key
		{"KEY_KEY_3", KEY_KEY_3}, // 3 key
		{"KEY_KEY_4", KEY_KEY_4}, // 4 key
		{"KEY_KEY_5", KEY_KEY_5}, // 5 key
		{"KEY_KEY_6", KEY_KEY_6}, // 6 key
		{"KEY_KEY_7", KEY_KEY_7}, // 7 key
		{"KEY_KEY_8", KEY_KEY_8}, // 8 key
		{"KEY_KEY_9", KEY_KEY_9}, // 9 key
		{"KEY_KEY_A", KEY_KEY_A}, // A key
		{"KEY_KEY_B", KEY_KEY_B}, // B key
		{"KEY_KEY_C", KEY_KEY_C}, // C key
		{"KEY_KEY_D", KEY_KEY_D}, // D key
		{"KEY_KEY_E", KEY_KEY_E}, // E key
		{"KEY_KEY_F", KEY_KEY_F}, // F key
		{"KEY_KEY_G", KEY_KEY_G}, // G key
		{"KEY_KEY_H", KEY_KEY_H}, // H key
		{"KEY_KEY_I", KEY_KEY_I}, // I key
		{"KEY_KEY_J", KEY_KEY_J}, // J key
		{"KEY_KEY_K", KEY_KEY_K}, // K key
		{"KEY_KEY_L", KEY_KEY_L}, // L key
		{"KEY_KEY_M", KEY_KEY_M}, // M key
		{"KEY_KEY_N", KEY_KEY_N}, // N key
		{"KEY_KEY_O", KEY_KEY_O}, // O key
		{"KEY_KEY_P", KEY_KEY_P}, // P key
		{"KEY_KEY_Q", KEY_KEY_Q}, // Q key
		{"KEY_KEY_R", KEY_KEY_R}, // R key
		{"KEY_KEY_S", KEY_KEY_S}, // S key
		{"KEY_KEY_T", KEY_KEY_T}, // T key
		{"KEY_KEY_U", KEY_KEY_U}, // U key
		{"KEY_KEY_V", KEY_KEY_V}, // V key
		{"KEY_KEY_W", KEY_KEY_W}, // W key
		{"KEY_KEY_X", KEY_KEY_X}, // X key
		{"KEY_KEY_Y", KEY_KEY_Y}, // Y key
		{"KEY_KEY_Z", KEY_KEY_Z}, // Z key
		{"KEY_LWIN", KEY_LWIN}, // Left Windows key (Microsoft® Natural® keyboard)
		{"KEY_RWIN", KEY_RWIN}, // Right Windows key (Natural keyboard)
		{"KEY_APPS", KEY_APPS}, // Applications key (Natural keyboard)
		{"KEY_SLEEP", KEY_SLEEP}, // Computer Sleep key
		{"KEY_NUMPAD0", KEY_NUMPAD0}, // Numeric keypad 0 key
		{"KEY_NUMPAD1", KEY_NUMPAD1}, // Numeric keypad 1 key
		{"KEY_NUMPAD2", KEY_NUMPAD2}, // Numeric keypad 2 key
		{"KEY_NUMPAD3", KEY_NUMPAD3}, // Numeric keypad 3 key
		{"KEY_NUMPAD4", KEY_NUMPAD4}, // Numeric keypad 4 key
		{"KEY_NUMPAD5", KEY_NUMPAD5}, // Numeric keypad 5 key
		{"KEY_NUMPAD6", KEY_NUMPAD6}, // Numeric keypad 6 key
		{"KEY_NUMPAD7", KEY_NUMPAD7}, // Numeric keypad 7 key
		{"KEY_NUMPAD8", KEY_NUMPAD8}, // Numeric keypad 8 key
		{"KEY_NUMPAD9", KEY_NUMPAD9}, // Numeric keypad 9 key
		{"KEY_MULTIPLY", KEY_MULTIPLY}, // Multiply key
		{"KEY_ADD", KEY_ADD}, // Add key
		{"KEY_SEPARATOR", KEY_SEPARATOR}, // Separator key
		{"KEY_SUBTRACT", KEY_SUBTRACT}, // Subtract key
		{"KEY_DECIMAL", KEY_DECIMAL}, // Decimal key
		{"KEY_DIVIDE", KEY_DIVIDE}, // Divide key
		{"KEY_F1", KEY_F1}, // F1 key
		{"KEY_F2", KEY_F2}, // F2 key
		{"KEY_F3", KEY_F3}, // F3 key
		{"KEY_F4", KEY_F4}, // F4 key
		{"KEY_F5", KEY_F5}, // F5 key
		{"KEY_F6", KEY_F6}, // F6 key
		{"KEY_F7", KEY_F7}, // F7 key
		{"KEY_F8", KEY_F8}, // F8 key
		{"KEY_F9", KEY_F9}, // F9 key
		{"KEY_F10", KEY_F10}, // F10 key
		{"KEY_F11", KEY_F11}, // F11 key
		{"KEY_F12", KEY_F12}, // F12 key
		{"KEY_F13", KEY_F13}, // F13 key
		{"KEY_F14", KEY_F14}, // F14 key
		{"KEY_F15", KEY_F15}, // F15 key
		{"KEY_F16", KEY_F16}, // F16 key
		{"KEY_F17", KEY_F17}, // F17 key
		{"KEY_F18", KEY_F18}, // F18 key
		{"KEY_F19", KEY_F19}, // F19 key
		{"KEY_F20", KEY_F20}, // F20 key
		{"KEY_F21", KEY_F21}, // F21 key
		{"KEY_F22", KEY_F22}, // F22 key
		{"KEY_F23", KEY_F23}, // F23 key
		{"KEY_F24", KEY_F24}, // F24 key
		{"KEY_NUMLOCK", KEY_NUMLOCK}, // NUM LOCK key
		{"KEY_SCROLL", KEY_SCROLL}, // SCROLL LOCK key
		{"KEY_LSHIFT", KEY_LSHIFT}, // Left SHIFT key
		{"KEY_RSHIFT", KEY_RSHIFT}, // Right SHIFT key
		{"KEY_LCONTROL", KEY_LCONTROL}, // Left CONTROL key
		{"KEY_RCONTROL", KEY_RCONTROL}, // Right CONTROL key
		{"KEY_LMENU", KEY_LMENU}, // Left MENU key
		{"KEY_RMENU", KEY_RMENU}, // Right MENU key
		{"KEY_OEM_1", KEY_OEM_1}, // for US ";:"
		{"KEY_PLUS", KEY_PLUS}, // Plus Key "+"
		{"KEY_COMMA", KEY_COMMA}, // Comma Key ","
		{"KEY_MINUS", KEY_MINUS}, // Minus Key "-"
		{"KEY_PERIOD", KEY_PERIOD}, // Period Key "."
		{"KEY_OEM_2", KEY_OEM_2}, // for US "/?"
		{"KEY_OEM_3", KEY_OEM_3}, // for US "`~"
		{"KEY_OEM_4", KEY_OEM_4}, // for US "[{"
		{"KEY_OEM_5", KEY_OEM_5}, // for US "\|"
		{"KEY_OEM_6", KEY_OEM_6}, // for US "]}"
		{"KEY_OEM_7", KEY_OEM_7}, // for US "'""
		{"KEY_OEM_8", KEY_OEM_8}, // None
		{"KEY_OEM_AX", KEY_OEM_AX}, // for Japan "AX"
		{"KEY_OEM_102", KEY_OEM_102}, // "<>" or "\|"
		{"KEY_ATTN", KEY_ATTN}, // Attn key
		{"KEY_CRSEL", KEY_CRSEL}, // CrSel key
		{"KEY_EXSEL", KEY_EXSEL}, // ExSel key
		{"KEY_EREOF", KEY_EREOF}, // Erase EOF key
		{"KEY_PLAY", KEY_PLAY}, // Play key
		{"KEY_ZOOM", KEY_ZOOM}, // Zoom key
		{"KEY_PA1", KEY_PA1}, // PA1 key
		{"KEY_OEM_CLEAR", KEY_OEM_CLEAR} // Clear key
	};
	//copy construct keys_ bimap
	keys_ = bimap(v.begin(), v.end());
}

const std::string& ControlKeyTranslation::getString(int value) const
{
	auto iter = keys_.right.find(value);

	if(iter == keys_.right.end()) {
		std::string("Failed to to fetch button with value " + std::to_string(value) + " from map!");
		BOOST_THROW_EXCEPTION(exception::BasicException(os));
	} 
		
	BOOST_LOG_TRIVIAL(debug)<<"Fetched "<<iter->second<<" with value "<<value<<" from map!";


	return iter->second;
}

int ControlKeyTranslation::getKey(std::string key) const
{
	auto iter = keys_.left.find(key);

	if(iter == keys_.left.end()) {
		std::string("Failed to to fetch value with key " + key + " from map!");
		BOOST_THROW_EXCEPTION(exception::BasicException(os));
	}
	
	BOOST_LOG_TRIVIAL(debug)<<"Fetched "<<iter->second<<" with value "<<key<" from map!";

	return iter->second;
}


const std::array<std::string,PLAYER_COUNT> Controls::playerIDs_ = {
	"PLAYER_1",	"PLAYER_2",	"PLAYER_3",	"PLAYER_4",
};


const std::array<std::string,Joypad::BUTTON_COUNT> Controls::directionIDs_ = {
	"UP","DOWN","LEFT","RIGHT","ENTER","INVENTORY","MENU"
};

Controls::Controls()
	:joysticks_(), keys_()
{

	for(auto iter = pressedKeys_.begin(); iter != pressedKeys_.end();  ++iter) {
		*iter = false;
	}

	fillControlMap();

	try {
		loadButtons();

	} catch (const exception::BasicException& exception) {
		FILE_LOG(logDEBUG1)<<"Failed to load controls from current configuration";
		FILE_LOG(logDEBUG1)<<exception.what();
		loadDefaultButtons();
	}
}

Controls::~Controls()
{
}

void Controls::loadButtons()
{
	for(size_t player = 0; player < PLAYER_COUNT; ++player) {

		std::vector<int> keyValues;

		for(size_t button = 0; button < Joypad::BUTTON_COUNT; ++button) {

			//read keys from ini
			std::string id(configuration::getConfigString(playerIDs_[player],directionIDs_[button]));

			//if id is not in configuration file alternative configuration false is returned
			auto iter = keys_.left.find(id);
			if(iter == keys_.left.end()) {
				joysticks_.clear();
				std::ostringstream os;
				os<<"Failed to read \""<<playerIDs_[player]<<"\" from section \""<<directionIDs_[button]<<"\"!";
				BOOST_THROW_EXCEPTION(exception::BasicException(os.str()));
			}

			//store integer value in buffer
			keyValues.push_back(iter->second);
		}

		//construct joystick with new values
		std::shared_ptr<Joypad> joypad(new Joypad(keyValues));

		joysticks_.push_back(joypad);
	}
}

void Controls::loadDefaultButtons()
{
	for(size_t player = 0; player < PLAYER_COUNT; ++player) {
		joysticks_.push_back(std::shared_ptr<Joypad> (new Joypad(player)));
	}
}

void Controls::setButton(size_t player,Joypad::BUTTON key, int value)
{
	set_config_string(playerIDs_[player].c_str(),directionIDs_[key].c_str(),getButton(value).c_str());
}

const std::string& Controls::getButton(int value) const
{
	auto iter = keys_.right.find(value);

	if(iter == keys_.right.end()) {
		std::ostringstream os;
		os<<"Failed to to fetch button with value "<<value<<" from map!";
		BOOST_THROW_EXCEPTION(exception::BasicException(os.str()));
	} else {
		FILE_LOG(logDEBUG4)<<"Fetched "<<iter->second<<" with value "<<value<<" from map!";
	}

	return iter->second;
}

const std::string& Controls::getButton(size_t player,Joypad::BUTTON button) const
{
	return getButton(joysticks_[player]->key[button]);
}

void Controls::fillKeyArray()
{
	for(auto iter = joysticks_.begin(); iter != joysticks_.end(); ++iter) {
		iter->get()->poll();
	}
}

bool Controls::getKey(size_t player, Joypad::BUTTON key) const
{
	return joysticks_[player]->button[key] != 0;
}

bool Controls::getDeprelledKey(size_t player, Joypad::BUTTON key)
{

	size_t index = player * Joypad::BUTTON_COUNT + key;

	//if button is pressed ...
	if(getKey(player,key)) {
		//if it was pressed last time -> pressedKeys_[index] is true, false is returned
		if(pressedKeys_[index])  {
			return false;
		} else {
			//else we set keyBuf to true and return true
			pressedKeys_[index] = true;
			return true;
		}
	}

	//if button is not pressed, the perspective entry in cnKeyBuf is set to false .... means key was not pressed last time function was called
	else {
		pressedKeys_[index] = false;
		//return false -> button is not pressed
		return false;
	}
}


void Controls::fillControlMap()
{


}
