#ifndef MESSAGES_H
#define MESSAGES_H

#include "messagingsystem.h"

/* CONTEXTS */

struct ActionInputContext {
	//refers to UserControls::Action
	int action_;
	//wether button was already pressed during the last frame
	bool wasDown_;
};

/* CONTEXTS END */

/* LISTENERS + SOURCES */

struct ActionInputListener {
	virtual void buttonDown(int action, bool wasDown) = 0;
	//virtual void mouseMoved() = 0;
};

typedef Messaging<ActionInputListener, ActionInputContext> ActionInputSource;


/* LISTENERS + SOURCES END*/

#endif // MESSAGES_H
