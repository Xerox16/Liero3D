#include "entitycomposer.h"

#include <functional>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "exception.h"
#include "entity.h"

EntityComposer::EntityComposer() : composers_()
{
}

void EntityComposer::registerComposer(const std::string& name, composer func)
{
	composers_[name] = func;
}

std::map<std::string, Entity::ptr> EntityComposer::readXML(const std::string& filename,  EntityCreationContext& context)
{
	std::map<std::string, Entity::ptr> entities;

	try {
	boost::property_tree::ptree pt;
	//read json
	boost::property_tree::json_parser::read_json(filename, pt);

	//iterate over json and create new entity for every entry
	for(auto entry = pt.begin(); entry != pt.end(); ++entry) {
		Entity::ptr entity(new Entity);
		BOOST_LOG_TRIVIAL(debug)<<"1. level first: "<<entry->first;
		
		//search entry for entity components
		for(auto component = entry->second.begin(); component != entry->second.end(); ++component) {
			auto composer = composers_.find(component->first);
			BOOST_LOG_TRIVIAL(debug)<<"2. level first: "<<entry->first;
		
			//add them to entity or throw exception if they were not found
			if(composer != composers_.end()) {
					composer->second(component->second, *entity, context);
			} else {
				BOOST_THROW_EXCEPTION(BasicException("invalid xml entry \"" + component->first + "\""));
			}
		}
			entities[entry->first] = entity;
	}
	
	//handle exceptions
	} catch(const boost::property_tree::ptree_bad_path& error) {
		BOOST_LOG_TRIVIAL(debug)<<"Invalid file: "<<"\""<<filename<<"\" Description: "<<boost::diagnostic_information(error);
	} catch(const boost::exception& error) {
		BOOST_LOG_TRIVIAL(debug)<<"Invalid xml structure in file: "<<"\""<<filename<<"\" ! Description: "<<boost::diagnostic_information(error);
	}

	return entities;
}
