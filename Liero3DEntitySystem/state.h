#ifndef STATE_H
#define STATE_H

#include <memory>

class State {
public:
    typedef std::shared_ptr<State> ptr;

public:
    State();
    virtual ~State();

    virtual State* clone() const = 0; //return copy-constructed copy of state allocated with new
};

#endif // STATE_H
