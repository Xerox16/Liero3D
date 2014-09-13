#ifndef SPACE_H
#define SPACE_H

#include <map>
#include <string>
#include <memory>

class Entity;

class Space
{
public:
	typedef std::shared_ptr<Space> ptr;

public:
	Space();
	Space(const Space& rhs); //copies space and all its entities, BEWARE: the keys remain the same for being able to access the newly created entities

	long addEntity(std::shared_ptr<Entity> entity);
	std::shared_ptr<Entity> getEntityPtr(long key) const;
	Entity* getEntity(long key) const;
	bool removeEntity(long key); //return true on success
	
	Space* clone() const; //copies space and all its entities using copy constructor

private:
	std::map <long, std::shared_ptr<Entity> > space_;

private:
	static long key_;
	static long getKey();
};


#endif // SPACE_H
