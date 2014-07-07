#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

#include "messagingsystem.h"
#include "constants.h"

class Entity;
class Object;

/* CONTEXTS */

struct EntityContext
{
    Entity* entity_;
};

/* CONTEXTS END */

/* LISTENERS + SOURCES */

struct PositionListener
{
    virtual void positionChanged(Entity* entity) = 0;
};

typedef
Messaging<PositionListener, EntityContext>
PositionSource;

struct MovementListener
{
    virtual void entityMoved(Entity* entity) = 0;
};

typedef
Messaging<MovementListener, EntityContext>
MovementSource;


struct ShotListener
{
    virtual void weaponFired(Entity* weapon) = 0;
};

typedef
Messaging<ShotListener, EntityContext>
ShotSource;




#endif // MESSAGES_H
