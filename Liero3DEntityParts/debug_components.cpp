#include "debug_components.h"

#include <boost/log/trivial.hpp>

#include "state.h"
#include "entity.h"
#include "action.h"

#include "exception.h"


Int* Int::clone() const
{
	return new Int(*this);
}


Double* Double::clone() const
{
	return new Double(*this);
}


AddToInt* AddToInt::clone() const
{
	return new AddToInt(*this);
}


void AddToInt::apply(Entity* target)
{
	auto int_ = target->getState<Int>();
	int_->i++;
}

AddToDouble* AddToDouble::clone() const
{
	return new AddToDouble(*this);
}

void AddToDouble::apply(Entity* target)
{
	auto double_ = target->getState<Double>();
	double_->d++;
}

void register_int(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	entity.addState(std::shared_ptr<Int>(new Int));
	entity.addType<Int>("int");
}

void register_add_to_int(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	entity.addAction(std::shared_ptr<AddToInt>(new AddToInt));
	entity.addType<AddToInt>("add_to_int");
}

void register_double(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	entity.addState(std::shared_ptr<Double>(new Double));
	entity.addType<Double>("double");
	Double* doubl = entity.getState<Double>();
	doubl->d = tree.get<double>("value");
}

void register_add_to_double(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	entity.addAction(std::shared_ptr<AddToDouble>(new AddToDouble));
	entity.addType<AddToDouble>("add_to_double");
}

void registerDebugComponents(EntityComposer& entityComposer)
{
	entityComposer.registerComposer("int",register_int);
	entityComposer.registerComposer("add_to_int",register_add_to_int);
	entityComposer.registerComposer("double",register_double);
	entityComposer.registerComposer("add_to_double",register_add_to_double);
}
