#define BOOST_LOG_DYN_LINK 1

#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "config.h"

Configuration::Configuration()
	:pt_()
{
}

void Configuration::load(const std::string& filename)
{
	boost::property_tree::json_parser::read_json(filename, pt_);
	BOOST_LOG_TRIVIAL(info) << "Loaded configuration file \"" << filename << "\"";
}

void Configuration::unload()
{
	pt_.clear();
}

int Configuration::getInt(const std::string& path) const
{
	int i = pt_.get<int>(path);
	return i;
}

std::string Configuration::getString(const std::string& path) const
{
	std::string str = pt_.get<std::string>(path);
	BOOST_LOG_TRIVIAL(info) << "Loaded string with value " << str << " with path "<< path ;
	return str;
}

float Configuration::getFloat(const std::string& path) const
{
	float f = pt_.get<float>(path);
	BOOST_LOG_TRIVIAL(info) << "Loaded float with value " << f << " with path "<< path ;
	return f;
}
