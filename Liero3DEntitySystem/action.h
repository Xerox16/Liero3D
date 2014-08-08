#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <memory>
#include <stddef.h>

class Entity;

class Action
{
public:
	typedef std::shared_ptr<Action> ptr;

public:
	Action();
	virtual ~Action();

//apply action to target_ if set, else to user_
	virtual void apply();
//pure virtual interface for cloning action
	virtual Action* clone() const = 0;
//manage user and target entity
	void setUser   (Entity* user);
	void setTarget (Entity* target);
	Entity* getUser()   const;
	Entity* getTarget() const;

protected:
//this is where the work is done
//pure virtual interface for whatever your action might want to do
	virtual void apply(Entity* target) = 0;

	Entity* user_;
	Entity* target_;
};


#endif // ACTION_H
