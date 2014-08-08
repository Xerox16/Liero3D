#ifndef MESSAGES_H
#define MESSAGES_H

#include "messagingsystem.h"

/* CONTEXTS */

struct ActionInputContext {
	//refers to UserControls::Action
	int action_ = 0;
	//whether button is down
	bool isDown_ = false;
	//whether button was already down during the last frame
	bool wasDown_ = false;
};

/* CONTEXTS END */

/* LISTENERS + SOURCES */

struct ActionInputListener {
	virtual void buttonStateChanged(int action, bool isDown, bool wasDown) = 0;
	//virtual void mouseMoved() = 0;
};

typedef Messaging<ActionInputListener, ActionInputContext> ActionInputSource;


/* LISTENERS + SOURCES END*/

#endif // MESSAGES_H
