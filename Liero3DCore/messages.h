#ifndef MESSAGES_H
#define MESSAGES_H

#include "messagingsystem.h"

/* CONTEXTS */

struct UserInputContext {
	int action;
};

/* CONTEXTS END */

/* LISTENERS + SOURCES */

struct UserInputListener {
	virtual void keyPressed(int action) = 0;
}

typedef Messaging<UserInputListener, UserInputContext> UserInputSource;


/* LISTENERS + SOURCES END*/

#endif // MESSAGES_H
