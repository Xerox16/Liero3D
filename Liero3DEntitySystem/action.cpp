#include "action.h"

//#include "exception.h"

Action::Action() : user_(NULL), target_(NULL) {
    //ctor
}

Action::~Action() {
    //dtor
}

void Action::apply() {
    if(!user_) {
        //BOOST_THROW_EXCEPTION(core::exception::AccessViolationException("Failed to apply action! Invalid \"user_\"-pointer!"));
    }

    //apply action to target if defined, otherwhise to user
    if(target_) {
        apply(target_);
    } else {
        apply(user_);
    }
}

void Action::setUser(Entity* user) {
    user_ = user;
}

void Action::setTarget(Entity* target) {
    target_ = target;
}

Entity* Action::getUser() const {
    return user_;
}

Entity* Action::getTarget() const {
    return target_;
}


