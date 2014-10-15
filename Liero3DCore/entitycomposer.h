#ifndef _ENTITY_COMPOSER_H_
#define _ENTITY_COMPOSER_H_

#include <string>
#include <functional>
#include <map>
#include <memory>

#include <boost/property_tree/ptree.hpp>

class Entity;
class MessageHub;

//hold references to objects required when initializing entity parts
struct EntityCreationContext {
    MessageHub* messageHub_; //heart of the messaging system, forward all messages
};


class EntityComposer {
public:
    typedef std::function<void(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)> composer;

public:
    EntityComposer();
    void registerComposer(const std::string& name, composer);
    std::map<std::string, std::shared_ptr<Entity> > readXML(const std::string& path, EntityCreationContext& context);

private:
    std::map<std::string,composer> composers_;
};

#endif // _ENTITY_COMPOSER_H_
