#include "entitycomposer.h"

#include <functional>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/extension/extension.hpp>

#include "../Liero3DEntitySystem/entity.h"

//void registerComponents(const EntityComposer& composer);
/*
EntityComposer::EntityComposer() : composers_() {
 using namespace boost::extensions;

  // In the Jamfile, shared libraries are set to have the same
  // prefix and extension, even on different operating systems.
  // This is for convenience in writing cross-platform code, but
  // is not required. All shared libraries are set to start with
  // "lib" and end with "extension".
  std::string library_path = "PongLibrary/bin/Debug/libPongLibrary.so";

  // Create shared_library object with the relative or absolute
  // path to the shared library.
  shared_library lib(library_path);

// Attempt to open the shared library.
  if (!lib.open()) {
    FILE_LOG(logERROR)<<"failed to open shared library";
  }

  std::function<void (EntityComposer& entityComposer)>
    registerComponents(lib.get<void, EntityComposer&>("registerComponents"));

// Check that the function was found.
  if (!registerComponents) {
    FILE_LOG(logERROR)<<"failed to retrieve register components function";
  }

  registerComponents(*this);
}

void EntityComposer::registerComposer(const std::string& name, composer func) {
    composers_[name] = func;
}

std::map<std::string, Entity::ptr> EntityComposer::readXML(const std::string& path, EntityCreationContext& context) {
    std::map<std::string, Entity::ptr> entities;

    try {

        boost::property_tree::ptree tree;
//read xml
        read_xml(path, tree);
//iterate over xml
        for(auto entry = tree.begin(); entry != tree.end(); ++entry) {
//create new entity for entry
            Entity::ptr entity(new Entity);

//search entry for entity parts
            for(auto component = entry->second.begin(); component != entry->second.end(); ++component) {

                auto composer = composers_.find(component->first);
//if available add them to entity object
                if(composer != composers_.end()) {
                    composer->second(component->second, *entity, context);
                } else {
                    BOOST_THROW_EXCEPTION((core::exception::BasicException("invalid xml entry \"" + component->first + "\"")));
                }

            }

            entities[entry->first] = entity;
        }

    } catch(const boost::property_tree::ptree_bad_path& error) {
        FILE_LOG(logDEBUG1)<<"Invalid file: "<<"\""<<path<<"\" Description: "<<boost::diagnostic_information(error);
    } catch(const boost::exception& error) {
        FILE_LOG(logDEBUG1)<<"Invalid xml structure in file: "<<"\""<<path<<"\" ! Description: "<<boost::diagnostic_information(error);
    }

    return entities;
}*/


