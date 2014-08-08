#include "space.h"

#include "entity.h"

long Space::key_ = 1;

long Space::getKey() {
    return key_++;
}

long Space::addEntity(Entity::ptr entity) {
    long key = getKey();
    entity->setKey(key);
    space_[key] = entity;
    return key;
}

Entity* Space::getEntity(long key) const {
    return getEntityPtr(key).get();
}

Entity::ptr Space::getEntityPtr(long key) const {
    auto iter = space_.find(key);
    if(iter != space_.end()) {
        return iter->second;
    }

    return Entity::ptr();
}

bool Space::removeEntity(long key) {
    auto iter = space_.find(key);
    if(iter != space_.end()) {
        space_.erase(iter);
        return true;
    }

    return false;
}

Space* Space::clone() const {
    Space* space = new Space;

    //copy entities
    for(auto entity : space_) {
        space->space_[entity.first] = Entity::ptr(entity.second->clone());
    }

    return space;
}
