#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE liero3d_test

#include <boost/test/unit_test.hpp>
#include <boost/exception/all.hpp> 

#include "header/utilities.h"
#include "header/config.h"

BOOST_AUTO_TEST_SUITE(core_test)

BOOST_AUTO_TEST_CASE(config_test) {
	//construct empty configuration
	Configuration config;
	//load config file
	config.load("/home/xerox/Programmierung/Projekte/Liero3D/assets/debug.json");
	//test functionality
	BOOST_REQUIRE(config.getInt("general.test_int") == 640);
	BOOST_REQUIRE(config.getString("general.test_string") == "Liero3D");
	//free memory
	config.unload();
	//check if memory was correctly freed
	BOOST_REQUIRE_THROW(config.getInt("general.widht"), boost::exception);
}


BOOST_AUTO_TEST_SUITE_END()