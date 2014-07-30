#include "controls.h"

#include <sstream>

#include "config.h"
#include "exception.h"

const std::array<std::string,PLAYER_COUNT> Controls::playerIDs_ = {
    "PLAYER_1",	"PLAYER_2",	"PLAYER_3",	"PLAYER_4", 
};


const std::array<std::string,Joypad::BUTTON_COUNT> Controls::directionIDs_ = {
    "UP","DOWN","LEFT","RIGHT","ENTER","INVENTORY","MENU"
};

Controls::Controls()
    :joysticks_(), keys_() {

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

Controls::~Controls() {
}

void Controls::loadButtons() {
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

void Controls::loadDefaultButtons() {
    for(size_t player = 0; player < PLAYER_COUNT; ++player) {
        joysticks_.push_back(std::shared_ptr<Joypad> (new Joypad(player)));
    }
}

void Controls::setButton(size_t player,Joypad::BUTTON key, int value) {
    set_config_string(playerIDs_[player].c_str(),directionIDs_[key].c_str(),getButton(value).c_str());
}

const std::string& Controls::getButton(int value) const {
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

const std::string& Controls::getButton(size_t player,Joypad::BUTTON button) const {
    return getButton(joysticks_[player]->key[button]);
}

void Controls::fillKeyArray() {
    for(auto iter = joysticks_.begin(); iter != joysticks_.end(); ++iter) {
        iter->get()->poll();
    }
}

bool Controls::getKey(size_t player, Joypad::BUTTON key) const {
    return joysticks_[player]->button[key] != 0;
}

bool Controls::getDeprelledKey(size_t player, Joypad::BUTTON key) {

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


void Controls::fillControlMap() {

    typedef boost::bimap<std::string,int>::value_type value_pair;

	enum EKEY_CODE
	{
		KEY_LBUTTON          = 0x01,  // Left mouse button
		KEY_RBUTTON          = 0x02,  // Right mouse button
		KEY_CANCEL           = 0x03,  // Control-break processing
		KEY_MBUTTON          = 0x04,  // Middle mouse button (three-button mouse)
		KEY_XBUTTON1         = 0x05,  // Windows 2000/XP: X1 mouse button
		KEY_XBUTTON2         = 0x06,  // Windows 2000/XP: X2 mouse button
		KEY_BACK             = 0x08,  // BACKSPACE key
		KEY_TAB              = 0x09,  // TAB key
		KEY_CLEAR            = 0x0C,  // CLEAR key
		KEY_RETURN           = 0x0D,  // ENTER key
		KEY_SHIFT            = 0x10,  // SHIFT key
		KEY_CONTROL          = 0x11,  // CTRL key
		KEY_MENU             = 0x12,  // ALT key
		KEY_PAUSE            = 0x13,  // PAUSE key
		KEY_CAPITAL          = 0x14,  // CAPS LOCK key
		KEY_KANA             = 0x15,  // IME Kana mode
		KEY_HANGUEL          = 0x15,  // IME Hanguel mode (maintained for compatibility use KEY_HANGUL)
		KEY_HANGUL           = 0x15,  // IME Hangul mode
		KEY_JUNJA            = 0x17,  // IME Junja mode
		KEY_FINAL            = 0x18,  // IME final mode
		KEY_HANJA            = 0x19,  // IME Hanja mode
		KEY_KANJI            = 0x19,  // IME Kanji mode
		KEY_ESCAPE           = 0x1B,  // ESC key
		KEY_CONVERT          = 0x1C,  // IME convert
		KEY_NONCONVERT       = 0x1D,  // IME nonconvert
		KEY_ACCEPT           = 0x1E,  // IME accept
		KEY_MODECHANGE       = 0x1F,  // IME mode change request
		KEY_SPACE            = 0x20,  // SPACEBAR
		KEY_PRIOR            = 0x21,  // PAGE UP key
		KEY_NEXT             = 0x22,  // PAGE DOWN key
		KEY_END              = 0x23,  // END key
		KEY_HOME             = 0x24,  // HOME key
		KEY_LEFT             = 0x25,  // LEFT ARROW key
		KEY_UP               = 0x26,  // UP ARROW key
		KEY_RIGHT            = 0x27,  // RIGHT ARROW key
		KEY_DOWN             = 0x28,  // DOWN ARROW key
		KEY_SELECT           = 0x29,  // SELECT key
		KEY_PRINT            = 0x2A,  // PRINT key
		KEY_EXECUT           = 0x2B,  // EXECUTE key
		KEY_SNAPSHOT         = 0x2C,  // PRINT SCREEN key
		KEY_INSERT           = 0x2D,  // INS key
		KEY_DELETE           = 0x2E,  // DEL key
		KEY_HELP             = 0x2F,  // HELP key
		KEY_KEY_0            = 0x30,  // 0 key
		KEY_KEY_1            = 0x31,  // 1 key
		KEY_KEY_2            = 0x32,  // 2 key
		KEY_KEY_3            = 0x33,  // 3 key
		KEY_KEY_4            = 0x34,  // 4 key
		KEY_KEY_5            = 0x35,  // 5 key
		KEY_KEY_6            = 0x36,  // 6 key
		KEY_KEY_7            = 0x37,  // 7 key
		KEY_KEY_8            = 0x38,  // 8 key
		KEY_KEY_9            = 0x39,  // 9 key
		KEY_KEY_A            = 0x41,  // A key
		KEY_KEY_B            = 0x42,  // B key
		KEY_KEY_C            = 0x43,  // C key
		KEY_KEY_D            = 0x44,  // D key
		KEY_KEY_E            = 0x45,  // E key
		KEY_KEY_F            = 0x46,  // F key
		KEY_KEY_G            = 0x47,  // G key
		KEY_KEY_H            = 0x48,  // H key
		KEY_KEY_I            = 0x49,  // I key
		KEY_KEY_J            = 0x4A,  // J key
		KEY_KEY_K            = 0x4B,  // K key
		KEY_KEY_L            = 0x4C,  // L key
		KEY_KEY_M            = 0x4D,  // M key
		KEY_KEY_N            = 0x4E,  // N key
		KEY_KEY_O            = 0x4F,  // O key
		KEY_KEY_P            = 0x50,  // P key
		KEY_KEY_Q            = 0x51,  // Q key
		KEY_KEY_R            = 0x52,  // R key
		KEY_KEY_S            = 0x53,  // S key
		KEY_KEY_T            = 0x54,  // T key
		KEY_KEY_U            = 0x55,  // U key
		KEY_KEY_V            = 0x56,  // V key
		KEY_KEY_W            = 0x57,  // W key
		KEY_KEY_X            = 0x58,  // X key
		KEY_KEY_Y            = 0x59,  // Y key
		KEY_KEY_Z            = 0x5A,  // Z key
		KEY_LWIN             = 0x5B,  // Left Windows key (Microsoft® Natural® keyboard)
		KEY_RWIN             = 0x5C,  // Right Windows key (Natural keyboard)
		KEY_APPS             = 0x5D,  // Applications key (Natural keyboard)
		KEY_SLEEP            = 0x5F,  // Computer Sleep key
		KEY_NUMPAD0          = 0x60,  // Numeric keypad 0 key
		KEY_NUMPAD1          = 0x61,  // Numeric keypad 1 key
		KEY_NUMPAD2          = 0x62,  // Numeric keypad 2 key
		KEY_NUMPAD3          = 0x63,  // Numeric keypad 3 key
		KEY_NUMPAD4          = 0x64,  // Numeric keypad 4 key
		KEY_NUMPAD5          = 0x65,  // Numeric keypad 5 key
		KEY_NUMPAD6          = 0x66,  // Numeric keypad 6 key
		KEY_NUMPAD7          = 0x67,  // Numeric keypad 7 key
		KEY_NUMPAD8          = 0x68,  // Numeric keypad 8 key
		KEY_NUMPAD9          = 0x69,  // Numeric keypad 9 key
		KEY_MULTIPLY         = 0x6A,  // Multiply key
		KEY_ADD              = 0x6B,  // Add key
		KEY_SEPARATOR        = 0x6C,  // Separator key
		KEY_SUBTRACT         = 0x6D,  // Subtract key
		KEY_DECIMAL          = 0x6E,  // Decimal key
		KEY_DIVIDE           = 0x6F,  // Divide key
		KEY_F1               = 0x70,  // F1 key
		KEY_F2               = 0x71,  // F2 key
		KEY_F3               = 0x72,  // F3 key
		KEY_F4               = 0x73,  // F4 key
		KEY_F5               = 0x74,  // F5 key
		KEY_F6               = 0x75,  // F6 key
		KEY_F7               = 0x76,  // F7 key
		KEY_F8               = 0x77,  // F8 key
		KEY_F9               = 0x78,  // F9 key
		KEY_F10              = 0x79,  // F10 key
		KEY_F11              = 0x7A,  // F11 key
		KEY_F12              = 0x7B,  // F12 key
		KEY_F13              = 0x7C,  // F13 key
		KEY_F14              = 0x7D,  // F14 key
		KEY_F15              = 0x7E,  // F15 key
		KEY_F16              = 0x7F,  // F16 key
		KEY_F17              = 0x80,  // F17 key
		KEY_F18              = 0x81,  // F18 key
		KEY_F19              = 0x82,  // F19 key
		KEY_F20              = 0x83,  // F20 key
		KEY_F21              = 0x84,  // F21 key
		KEY_F22              = 0x85,  // F22 key
		KEY_F23              = 0x86,  // F23 key
		KEY_F24              = 0x87,  // F24 key
		KEY_NUMLOCK          = 0x90,  // NUM LOCK key
		KEY_SCROLL           = 0x91,  // SCROLL LOCK key
		KEY_LSHIFT           = 0xA0,  // Left SHIFT key
		KEY_RSHIFT           = 0xA1,  // Right SHIFT key
		KEY_LCONTROL         = 0xA2,  // Left CONTROL key
		KEY_RCONTROL         = 0xA3,  // Right CONTROL key
		KEY_LMENU            = 0xA4,  // Left MENU key
		KEY_RMENU            = 0xA5,  // Right MENU key
		KEY_OEM_1            = 0xBA,  // for US    ";:"
		KEY_PLUS             = 0xBB,  // Plus Key   "+"
		KEY_COMMA            = 0xBC,  // Comma Key  ","
		KEY_MINUS            = 0xBD,  // Minus Key  "-"
		KEY_PERIOD           = 0xBE,  // Period Key "."
		KEY_OEM_2            = 0xBF,  // for US    "/?"
		KEY_OEM_3            = 0xC0,  // for US    "`~"
		KEY_OEM_4            = 0xDB,  // for US    "[{"
		KEY_OEM_5            = 0xDC,  // for US    "\|"
		KEY_OEM_6            = 0xDD,  // for US    "]}"
		KEY_OEM_7            = 0xDE,  // for US    "'""
		KEY_OEM_8            = 0xDF,  // None
		KEY_OEM_AX           = 0xE1,  // for Japan "AX"
		KEY_OEM_102          = 0xE2,  // "<>" or "\|"
		KEY_ATTN             = 0xF6,  // Attn key
		KEY_CRSEL            = 0xF7,  // CrSel key
		KEY_EXSEL            = 0xF8,  // ExSel key
		KEY_EREOF            = 0xF9,  // Erase EOF key
		KEY_PLAY             = 0xFA,  // Play key
		KEY_ZOOM             = 0xFB,  // Zoom key
		KEY_PA1              = 0xFD,  // PA1 key
		KEY_OEM_CLEAR        = 0xFE,   // Clear key

		KEY_KEY_CODES_COUNT  = 0xFF // this is not a key, but the amount of keycodes there are.
    //simply fills keys_ with values
    keys_.insert(value_pair("A",KEY_A));
    keys_.insert(value_pair("B",KEY_B));
    keys_.insert(value_pair("C",KEY_C));
    keys_.insert(value_pair("D",KEY_D));
    keys_.insert(value_pair("E",KEY_E));
    keys_.insert(value_pair("F",KEY_F));
    keys_.insert(value_pair("G",KEY_G));
    keys_.insert(value_pair("H",KEY_H));
    keys_.insert(value_pair("I",KEY_I));
    keys_.insert(value_pair("J",KEY_J));
    keys_.insert(value_pair("K",KEY_K));
    keys_.insert(value_pair("L",KEY_L));
    keys_.insert(value_pair("M",KEY_M));
    keys_.insert(value_pair("N",KEY_N));
    keys_.insert(value_pair("O",KEY_O));
    keys_.insert(value_pair("P",KEY_P));
    keys_.insert(value_pair("Q",KEY_Q));
    keys_.insert(value_pair("R",KEY_R));
    keys_.insert(value_pair("S",KEY_S));
    keys_.insert(value_pair("T",KEY_T));
    keys_.insert(value_pair("U",KEY_U));
    keys_.insert(value_pair("V",KEY_V));
    keys_.insert(value_pair("W",KEY_W));
    keys_.insert(value_pair("X",KEY_X));
    keys_.insert(value_pair("Y",KEY_Y));
    keys_.insert(value_pair("Z",KEY_Z));

    keys_.insert(value_pair("0",KEY_0));
    keys_.insert(value_pair("1",KEY_1));
    keys_.insert(value_pair("2",KEY_2));
    keys_.insert(value_pair("3",KEY_3));
    keys_.insert(value_pair("4",KEY_4));
    keys_.insert(value_pair("5",KEY_5));
    keys_.insert(value_pair("6",KEY_6));
    keys_.insert(value_pair("7",KEY_7));
    keys_.insert(value_pair("8",KEY_8));
    keys_.insert(value_pair("9",KEY_9));

    keys_.insert(value_pair("0_PAD",KEY_0_PAD));
    keys_.insert(value_pair("1_PAD",KEY_1_PAD));
    keys_.insert(value_pair("2_PAD",KEY_2_PAD));
    keys_.insert(value_pair("3_PAD",KEY_3_PAD));
    keys_.insert(value_pair("4_PAD",KEY_4_PAD));
    keys_.insert(value_pair("5_PAD",KEY_5_PAD));
    keys_.insert(value_pair("6_PAD",KEY_6_PAD));
    keys_.insert(value_pair("7_PAD",KEY_7_PAD));
    keys_.insert(value_pair("8_PAD",KEY_8_PAD));
    keys_.insert(value_pair("9_PAD",KEY_9_PAD));

    keys_.insert(value_pair("F1",KEY_F1));
    keys_.insert(value_pair("F2",KEY_F2));
    keys_.insert(value_pair("F3",KEY_F3));
    keys_.insert(value_pair("F4",KEY_F4));
    keys_.insert(value_pair("F5",KEY_F5));
    keys_.insert(value_pair("F6",KEY_F6));
    keys_.insert(value_pair("F7",KEY_F7));
    keys_.insert(value_pair("F8",KEY_F8));
    keys_.insert(value_pair("F9",KEY_F9));
    keys_.insert(value_pair("F10",KEY_F10));
    keys_.insert(value_pair("F11",KEY_F11));
    keys_.insert(value_pair("F12",KEY_F12));

    keys_.insert(value_pair("ESC",KEY_ESC));
    keys_.insert(value_pair("TILDE",KEY_TILDE));
    keys_.insert(value_pair("MINUS",KEY_MINUS));
    keys_.insert(value_pair("EQUALS",KEY_EQUALS));
    keys_.insert(value_pair("BACKSPACE",KEY_BACKSPACE));
    keys_.insert(value_pair("TAB",KEY_TAB));
    keys_.insert(value_pair("OPENBRACE",KEY_OPENBRACE));
    keys_.insert(value_pair("CLOSEBRACE",KEY_CLOSEBRACE));
    keys_.insert(value_pair("ENTER",KEY_ENTER));
    keys_.insert(value_pair("COLON",KEY_COLON));
    keys_.insert(value_pair("QUOTE",KEY_QUOTE));
    keys_.insert(value_pair("BACKSLASH",KEY_BACKSLASH));
    keys_.insert(value_pair("BACKSLASH2",KEY_BACKSLASH2));
    keys_.insert(value_pair(",",KEY_COMMA));
    keys_.insert(value_pair("STOP",KEY_STOP));
    keys_.insert(value_pair("SLASH",KEY_SLASH));
    keys_.insert(value_pair("SPACE",KEY_SPACE));
    keys_.insert(value_pair("INSERT",KEY_INSERT));
    keys_.insert(value_pair("DEL",KEY_DEL));
    keys_.insert(value_pair("HOME",KEY_HOME));
    keys_.insert(value_pair("END",KEY_END));
    keys_.insert(value_pair("PGUP",KEY_PGUP));
    keys_.insert(value_pair("PGDN",KEY_PGDN));

    keys_.insert(value_pair("LEFT",KEY_LEFT));
    keys_.insert(value_pair("RIGHT",KEY_RIGHT));
    keys_.insert(value_pair("UP",KEY_UP));
    keys_.insert(value_pair("DOWN",KEY_DOWN));

    keys_.insert(value_pair("SLASH_PAD",KEY_SLASH_PAD));
    keys_.insert(value_pair("ASTERISK",KEY_ASTERISK));
    keys_.insert(value_pair("MINUS_PAD",KEY_MINUS_PAD));
    keys_.insert(value_pair("PLUS_PAD",KEY_PLUS_PAD));
    keys_.insert(value_pair("DEL_PAD",KEY_DEL_PAD));
    keys_.insert(value_pair("ENTER_PAD",KEY_ENTER_PAD));
    keys_.insert(value_pair("PRTSCR",KEY_PRTSCR));
    keys_.insert(value_pair("PAUSE",KEY_PAUSE));
    keys_.insert(value_pair("ABNT_C1",KEY_ABNT_C1));
    keys_.insert(value_pair("YEN",KEY_YEN));
    keys_.insert(value_pair("KANA",KEY_KANA));
    keys_.insert(value_pair("CONVERT",KEY_CONVERT));
    keys_.insert(value_pair("NOCONVERT",KEY_NOCONVERT));

    keys_.insert(value_pair("@",KEY_AT));
    keys_.insert(value_pair("^",KEY_CIRCUMFLEX));
    keys_.insert(value_pair("COLON2",KEY_COLON2));
    keys_.insert(value_pair("KANJI",KEY_KANJI));
    keys_.insert(value_pair("LSHIFT",KEY_LSHIFT));
    keys_.insert(value_pair("RSHIFT",KEY_RSHIFT));
    keys_.insert(value_pair("LCONTROL",KEY_LCONTROL));
    keys_.insert(value_pair("RCONTROL",KEY_RCONTROL));

    keys_.insert(value_pair("ALT",KEY_ALT));
    keys_.insert(value_pair("ALTGR",KEY_ALTGR));
    keys_.insert(value_pair("LWIN",KEY_LWIN));
    keys_.insert(value_pair("RWIN",KEY_RWIN));
    keys_.insert(value_pair("MENU",KEY_MENU));
    keys_.insert(value_pair("SCRLOCK",KEY_SCRLOCK));
    keys_.insert(value_pair("NUMLOCK",KEY_NUMLOCK));
    keys_.insert(value_pair("CAPSLOCK",KEY_CAPSLOCK));
    keys_.insert(value_pair("EQUALS_PAD",KEY_EQUALS_PAD));
    keys_.insert(value_pair("BACKQUOTE",KEY_BACKQUOTE));
    keys_.insert(value_pair(";",KEY_SEMICOLON));
    keys_.insert(value_pair("COMMAND",KEY_COMMAND));
}

}

