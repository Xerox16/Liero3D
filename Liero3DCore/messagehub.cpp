#include "messagehub.h"


void MessageHub::buttonStateChanged(int action, bool isDown, bool wasDown) {
	ActionInputContext context;
	context.action_ = action;
	context.isDown_ = isDown;
	context.wasDown_ = wasDown;
	ActionInputSource::raiseEvent(context);
}

void MessageHub::dispatchEvent(ActionInputListener* p, const ActionInputContext& context) {
	p->buttonStateChanged(context.action_, context.isDown_, context.wasDown_);
}