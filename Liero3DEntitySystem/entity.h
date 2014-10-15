#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <set>
#include <memory>
#include <typeindex>
#include <typeinfo>

//forward declarations
class Space;
class State;
class Action;

class Entity
{
public:
	typedef std::shared_ptr<Entity> ptr;

public:
	Entity();
	Entity(const Entity& rhs); //copies entity and all its components
	virtual ~Entity();

	//manage unique entity key
	long getKey() const;
	void setKey(long key);
	
	//set space entity resides in
	void setSpace(Space* space);
	Space* getSpace() const;
	
	//add entity components
	void addState   (std::shared_ptr<State> state);
	void addAction  (std::shared_ptr<Action> action);

	//get pointers to entity components
	template <typename T> std::shared_ptr<T>  getStatePtr () const;
	template <typename T> std::shared_ptr<T>  getActionPtr() const;
	template <typename T> T* getState  () const;
	template <typename T> T* getAction () const;
	
	//remove entity components
	template <typename T> void removeState();
	template <typename T> void removeAction();
	
	//use action, target == NULL equals target == this
	template <typename T> bool useAction(Entity* target = NULL);
	
	//manage updated actions that can be applied with low overhead with updateActions
	template <typename T> void enableActionUpdate();
	template <typename T> void disableActionUpdate();
	void updateActions();	
	
	//clones entire Entity, references to other objects (space_, states_) are not simply copied, but these objects are cloned
	Entity* clone() const; 

protected:
	long key_;
	Space* space_;
	std::map<std::type_index, std::shared_ptr<State> >  states_;
	std::map<std::type_index, std::shared_ptr<Action> > actions_;
	std::set<std::type_index> updatedActions_; //used actions are called every frame as long as they exist
};

#include "entity.inc"

#endif // ENTITY_H
