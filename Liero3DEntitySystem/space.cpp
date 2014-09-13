#include "space.h"

#include "entity.h"

long Space::key_ = 1;

long Space::getKey()
{
	return key_++;
}

Space::Space() : space_() {
}

Space::Space(const Space& rhs) : space_() {
	//clone entities
	for(auto entity : rhs.space_) {
		space_[entity.first] = Entity::ptr(entity.second->clone());
	}
	//set entities' space pointers to this space
	for(auto entity : space_) {
		entity.second->setSpace(this);
	}
}


long Space::addEntity(Entity::ptr entity)
{
	entity->setKey(getKey());
	space_[entity->getKey()] = entity;
	return entity->getKey();
}

Entity* Space::getEntity(long key) const
{
	return getEntityPtr(key).get();
}

Entity::ptr Space::getEntityPtr(long key) const
{
	auto iter = space_.find(key);
	if(iter != space_.end()) {
		return iter->second;
	} else {
		return Entity::ptr();
	}
}

bool Space::removeEntity(long key)
{
	auto iter = space_.find(key);
	if(iter != space_.end()) {
		space_.erase(iter);
		return true;
	} else {
		return false;
	}
}

Space* Space::clone() const
{
	return new Space(*this);
}
