#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE liero3d_test

#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/exception/all.hpp> 

#include "header/utilities.h"
#include "header/config.h"
#include "header/messagingsystem.h"

using namespace std;

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

/* Declare classes needed for messaging test outside test */

// some listener interface
struct MartianAlertListener
{
    virtual void martianLanded(const string &where) = 0;
};
// a commong functionality of the normal person
class Person
{
public:
    Person(const string &name) : name_(name) {}
    string getName() const { return name_; }
private:
    string name_;
};

// a class representing the normal person
// normal person is interested in the MartianAlert events
class NormalPerson : public Person,
public MartianAlertListener
{
public:
    NormalPerson(const string &name)
        : Person(name) {}

    // here, the Person receives the notification
    virtual void martianLanded(const string &where)
    {
        where_ = where;
    }
	
	std::string where_;
};

// a context structure for MartianAlert events,
// holding the info considering the landing place
struct MartianContext
{
    string where_;
};

// the helper typedef
typedef
Messaging<MartianAlertListener, MartianContext>
MartianAlertSource;

// the ultimate source of events
class EventSource : public MartianAlertSource
{
public:
    // inherited from MartianAlertSource
    void dispatchEvent(MartianAlertListener *p,
                const MartianContext &context)
    {
        // just call the listener
        p->martianLanded(context.where_);
    }
    // play a little with events
    void sendEarth()
    {
        // send a martian alert

        MartianContext ctx1;
        ctx1.where_ = "Earth";

        // note: if this class inherits from
        // only one event source base,
        // the operator:: is not needed
        MartianAlertSource::raiseEvent(ctx1);
    }
	
	// play a little with events
    void sendPluto()
    {
        // send a martian alert

        MartianContext ctx1;
        ctx1.where_ = "Pluto";

        // note: if this class inherits from
        // only one event source base,
        // the operator:: is not needed
        MartianAlertSource::raiseEvent(ctx1);
    }
};

BOOST_AUTO_TEST_CASE(messaging_test) {
    // event notifications:
    NormalPerson john("John");
    NormalPerson jenny("Jenny");

    // this is a source of events
    EventSource source;

    // register objects as listeners in an event source
    // note: if an event source inherits from only one
    // event source base, the :: selectors are not needed
    source.MartianAlertSource::addListener(&john);
    source.MartianAlertSource::addListener(&jenny);
	
    // send earth message
    source.sendEarth();
	
	//check if sending messages + adding listeners works
	BOOST_REQUIRE_EQUAL(john.where_, "Earth");
	BOOST_REQUIRE_EQUAL(jenny.where_, "Earth");
}


BOOST_AUTO_TEST_CASE(messaging_hub_test) {
    // event notifications:
    NormalPerson john("John");
    NormalPerson jenny("Jenny");

    // this is a source of events
    EventSource source;

    // register objects as listeners in an event source
    // note: if an event source inherits from only one
    // event source base, the :: selectors are not needed
    source.MartianAlertSource::addListener(&john);
    source.MartianAlertSource::addListener(&jenny);
	
    // send earth message
    source.sendEarth();
	
	//check if sending messages + adding listeners works
	BOOST_REQUIRE_EQUAL(john.where_, "Earth");
	BOOST_REQUIRE_EQUAL(jenny.where_, "Earth");
}


BOOST_AUTO_TEST_SUITE_END()