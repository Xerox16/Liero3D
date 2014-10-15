#ifndef MESSAGINGMANAGER_H
#define MESSAGINGMANAGER_H

#include "messages.h"

class MessageHub : public ActionInputListener, public ActionInputSource
{
public:
	void buttonStateChanged(int action, bool isDown, bool wasDown);
	void dispatchEvent(ActionInputListener* p, const ActionInputContext& context);
};

#endif // MESSAGINGMANAGER_H
