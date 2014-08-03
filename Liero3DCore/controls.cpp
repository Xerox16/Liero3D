#include <sstream>
#include <boost/log/trivial.hpp>

#include "controls.h"
#include "config.h"
#include "exception.h"

using namespace irr;

//DEFINITION OF KEY2STRING

Key2String::Key2String()
	:keys_()
{
	//define helper typedefs
	typedef boost::bimap<std::string,irr::EKEY_CODE> bimap;
	typedef bimap::value_type value_pair;

	//initialize vector of value pairs with initializer list since boost::bimap does not support initializer lists
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
	//copy construct bimap
	keys_ = bimap(v.begin(), v.end());
}

const std::string& Key2String::getString(irr::EKEY_CODE key) const
{
	auto iter = keys_.right.find(key);

	if(iter == keys_.right.end()) {
		std::string error("Key2String: Failed to to fetch string with key " + std::to_string(key) + " from map!");
		throw BasicException(error);
	}

	BOOST_LOG_TRIVIAL(debug)<<"Fetched "<<iter->second<<" with key "<<key<<" from map!";


	return iter->second;
}

irr::EKEY_CODE Key2String::getKey(const std::string& string_) const
{
	auto iter = keys_.left.find(string_);

	if(iter == keys_.left.end()) {
		std::string error("Key2String: Failed to to fetch key with " + string_ + " from map!");
		throw BasicException(error);
	}

	BOOST_LOG_TRIVIAL(debug)<<"Fetched "<<iter->second<<" with string "<<string_<<" from map!";

	return iter->second;
}

//DEFINITION OF USERCONTROLS

const std::array<std::string, UserControls::ACTION_COUNT> UserControls::actions_ = {
	"UP","DOWN","LEFT","RIGHT","ENTER","INVENTORY","MENU"
};


void UserControls::dispatchEvent(ActionInputListener *listener,  const ActionInputContext &context)
{
	listener->buttonDown(context.action_, context.wasDown_);
}

void UserControls::loadProfile(const std::string& profile, const Configuration& configuration, const Key2String& k2s)
{
	keys_.clear();

	//load key string from configuration, translate it to irrlicht hex value, store hex value in key vector
	for(auto iter = actions_.begin(); iter != actions_.end(); ++iter) {
		//build configuration string
		std::ostringstream os;
		os<<"profiles."<<profile<<"."<<*iter;
		//fetch key by entry in config file
		keys_.push_back(k2s.getKey(configuration.getString(os.str())));
	}
}

void UserControls::updateInput(EventReceiver& eventReceiver)
{
	//handle keyboard
	for(int i = 0; i < ACTION_COUNT; ++i) {
		if(eventReceiver.isKeyDown(keys_[i])) {
			ActionInputContext context;
			context.action_ = i;

			//deprel keys
			if(eventReceiver.wasKeyDown(keys_[i])) {
				context.wasDown_ = true;
			} else {
				context.wasDown_ = false;
			}

			ActionInputSource::raiseEvent(context);
		}
	}
}
