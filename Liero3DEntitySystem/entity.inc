#include "space.h"
#include "state.h"
#include "action.h"


Entity::Entity() :  key_(-1), space_(), states_(), actions_(), updatedActions_()
{
}

Entity::Entity(const Entity& rhs) : key_(rhs.key_), space_(rhs.space_), states_(), actions_(), updatedActions_(rhs.updatedActions_.begin(), rhs.updatedActions_.end()), types_(rhs.types_)
{
	//iterate over all states
	for(auto& state : rhs.states_) {
		//make a copy of each state
		State::ptr statePtr(state.second->clone());
		//store copy in entity
		addState(statePtr);
	}

	//iterate over all actions
	for(auto& action : rhs.actions_) {
		//make a copy of each action
		Action::ptr actionPtr(action.second->clone());
		//set new action user
		actionPtr->setUser(this);
		//store copy in entity
		addAction(actionPtr);
	}
}

Entity::~Entity()
{
}


long Entity::getKey() const
{
	return key_;
}

void Entity::setKey(long key)
{
	key_ = key;
}

void Entity::setSpace(Space* space) 
{
	space_ = space;
}

Space* Entity::getSpace() const {
	return space_;
}

void Entity::addState(std::shared_ptr<State> state)
{
	states_[std::type_index(typeid(*state))] = state; //save state with class type of state as key
}

void Entity::addAction(std::shared_ptr<Action> action)
{
	actions_[std::type_index(typeid(*action))] = action; //save state with class type of state as key
}

/*
template <typename T> void Entity::addType(const std::string& id) 
{
	std::type_index index(typeid(T));
	types_[id] = index;
}*/

void Entity::addType(std::shared_ptr<State> state, const std::string& id) 
{
	types_[id] = std::type_index(typeid(*state));
}


template <typename T> std::shared_ptr<T>  Entity::getStatePtr () const
{
	std::type_index index(typeid(T));
	auto iter = states_.find(index);
	if(iter != states_.end()) {
		return std::static_pointer_cast<T>(iter->second);
	} else {
		return std::shared_ptr<T>();
	}
}

template <typename T> std::shared_ptr<T>  Entity::getActionPtr() const
{
	std::type_index index(typeid(T));
	auto iter = actions_.find(index);
	if(iter != actions_.end()) {
		return std::static_pointer_cast<T>(iter->second);
	} else {
		return std::shared_ptr<T>();
	}
}

template <typename T> T* Entity::getState() const
{
	return getStatePtr<T>().get();
}

template <typename T> T* Entity::getAction() const
{
	return getActionPtr<T>().get();
}


std::shared_ptr<State>  Entity::getStatePtr (const std::string& id) const 
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return std::shared_ptr<State>();
	}
	
	auto iter = states_.find(type->second);
	if(iter != states_.end()) {
		return std::shared_ptr<State>(iter->second);
	} else {
		return std::shared_ptr<State>();
	}
}

std::shared_ptr<Action> Entity::getActionPtr(const std::string& id) const
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return std::shared_ptr<Action>();
	}
	
	auto iter = actions_.find(type->second);
	if(iter != actions_.end()) {
		return std::shared_ptr<Action>(iter->second);
	} else {
		return std::shared_ptr<Action>();
	}
}

State* Entity::getState  (const std::string& id) const 
{
	return getStatePtr(id).get();
}

Action* Entity::getAction (const std::string& id) const 
{
	return getActionPtr(id).get();
}

template <typename T> void Entity::removeState()
{
	std::type_index index(typeid(T));
	auto iter = states_.find(index);
	if(iter != states_.end()) {
		states_.erase(iter);
	}
}

template <typename T> void Entity::removeAction()
{
	std::type_index index(typeid(T));
	auto iter = actions_.find(index);
	if(iter != actions_.end()) {
		actions_.erase(iter);
	}
}


void Entity::removeState(const std::string& id)
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return;
	}
	
	auto iter = states_.find(type->second);
	if(iter != states_.end()) {
		states_.erase(iter);
	}
}

void Entity::removeAction(const std::string& id)
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return;
	}
	
	auto iter = actions_.find(type->second);
	if(iter != actions_.end()) {
		actions_.erase(iter);
	}
}


template <typename T> bool Entity::useAction(Entity* target)
{
	std::type_index index(typeid(T));
	auto iter = actions_.find(index);
	if(iter != actions_.end()) {
		if(target != NULL) {
			iter->second->setTarget(target);
		}
		iter->second->apply();

		return true;
	} else {
		return false;
	}
}

template <typename T> void Entity::enableActionUpdate()
{
	std::type_index index(typeid(T));
	if(actions_.count(index) != 0) {
		updatedActions_.insert(index);
	}
}

template <typename T> void Entity::disableActionUpdate()
{
	std::type_index index(typeid(T));
	auto iter = updatedActions_.find(index);
	if(iter != updatedActions_.end()) {
		updatedActions_.erase(iter);
	}
}




bool Entity::useAction(const std::string& id, Entity* target)
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return false;
	}
	
	auto iter = actions_.find(type->second);
	if(iter != actions_.end()) {
		if(target != NULL) {
			iter->second->setTarget(target);
		}
		iter->second->apply();

		return true;
	} else {
		return false;
	}
}

void Entity::enableActionUpdate(const std::string& id)
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return;
	}
	
	if(actions_.count(type->second) != 0) {
		updatedActions_.insert(type->second);
	}
}

void Entity::disableActionUpdate(const std::string& id)
{
	auto type = types_.find(id);
	if(type == types_.end()) {
		return;
	}
	
	auto iter = updatedActions_.find(type->second);
	if(iter != updatedActions_.end()) {
		updatedActions_.erase(iter);
	}
}


void Entity::updateActions()
{
	for(auto& action : updatedActions_) {
		actions_[action]->apply();
	}
}

Entity* Entity::clone() const
{
	return new Entity(*this);
}
