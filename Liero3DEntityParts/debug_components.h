#ifndef _MAIN_LIERO_H_
#define _MAIN_LIERO_H_

#include "entitycomposer.h"
#include "state.h"
#include "action.h"
#include "entity.h"

void registerDebugComponents(EntityComposer& entityComposer);


class Int : public State
{
public:
	Int* clone() const;
	int i = 0;
};

class Double : public State
{
public:
	Double* clone() const;
	double d = 0.0;
};

class AddToInt : public Action
{
public:
	AddToInt* clone() const;
	int cloneTest = 0;

protected:
	void apply(Entity* target);
};

class AddToDouble : public Action
{
public:
	AddToDouble* clone() const;

protected:
	void apply(Entity* target);
};
#endif