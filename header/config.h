#ifndef _CONFIGURATION_HANDLER_
#define _CONFIGURATION_HANDLER_

#include <boost/property_tree/ptree.hpp>

class Configuration
{
public:
	Configuration();
//load json-file with given path
	void load(const std::string& filename);
//free memory from configuration file
	void unload();
//get integer from configuration file, throw exception if path is invalid
	int getInt(const std::string& path) const;
//get string from configuration file, throw exception if path is invalid
	std::string getString(const std::string& path) const;
//BEWARE: floating point inaccuracy
	float getFloat(const std::string& path) const;

private:
	boost::property_tree::ptree pt_; //json file
};


#endif
