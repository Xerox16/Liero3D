#ifndef SPACE_H
#define SPACE_H

#include <map>
#include <string>
#include <memory>

class Entity;

class Space {
public:
    typedef std::shared_ptr<Space> ptr;

public:
    long addEntity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> getEntityPtr(long key) const;
    Entity* getEntity(long key) const;
    bool removeEntity(long key); //returns true on success

//entirely copies entities and subspaces with corresponding clone-methods, copy holds references to cloned entities and spaces
    Space* clone() const;
	
    std::map <long, std::shared_ptr<Entity> > space_;

private:

    static long getKey();
    static long key_;
};


#endif // SPACE_H
