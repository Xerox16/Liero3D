#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <set>
#include <memory>
#include <typeinfo>
#include <typeindex>

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
	
	//add component types
	template <typename T> void addType(const std::string& id); //add type to types_ for resolving component types from strings
	//void addType(std::shared_ptr<State> state, const std::string& id); //add type to types_ for resolving component types from strings

	//get pointers to entity components
	template <typename T> std::shared_ptr<T>  getStatePtr () const;
	template <typename T> std::shared_ptr<T>  getActionPtr() const;
	template <typename T> T* getState  () const;
	template <typename T> T* getAction () const;
	
	//get pointers to entity component base classes if type is unknown
	std::shared_ptr<State>  getStatePtr (const std::string& id) const;
	std::shared_ptr<Action>  getActionPtr(const std::string& id) const;
	State* getState  (const std::string& id) const;
	Action* getAction (const std::string& id) const;
	
	//remove entity components
	template <typename T> void removeState();
	template <typename T> void removeAction();
	
	//remove entity component if type is unknown
	void removeState(const std::string& id);
	void removeAction(const std::string& id);
	
	//use action, target == NULL equals target == this
	template <typename T> bool useAction(Entity* target = NULL);
	bool useAction(const std::string& id, Entity* target = NULL);
	
	//manage updated actions that can be applied with low overhead with updateActions
	template <typename T> void enableActionUpdate();
	template <typename T> void disableActionUpdate();
	void enableActionUpdate(const std::string& id);
	void disableActionUpdate(const std::string& id);
	
	void updateActions();	
	
	
	//clones entire Entity, references to other objects (space_, states_) are not simply copied, but these objects are cloned
	Entity* clone() const; 

protected:
	long key_;
	Space* space_;
	std::map<std::type_index, std::shared_ptr<State> >  states_;
	std::map<std::type_index, std::shared_ptr<Action> > actions_;
	std::set<std::type_index> updatedActions_; //used actions are called every frame as long as they exist
	std::map<std::string, std::type_index> types_; //translates names of types to types so that states, actions... can be retrieved without knowing the actual object type
};

#include "entity.inc"

#endif // ENTITY_H
