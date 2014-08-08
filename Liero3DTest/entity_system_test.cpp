#include "defines.h"

#include <boost/log/trivial.hpp>
#include <boost/exception/all.hpp>

#include "state.h"
#include "action.h"
#include "entity.h"
#include "space.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(entity_system_test)

class Int : public State {
public:
	Int* clone() const {
		return new Int(*this);
	};
	
	int i = 0;
};

class Double : public State {
public:
	Double* clone() const {
		return new Double(*this);
	};
	
	double d = 0.0;
};



BOOST_AUTO_TEST_CASE(state_test)
{
	Int int_;
	Int* int_copy = int_.clone();
	delete int_copy;	
}

BOOST_AUTO_TEST_CASE(action_test)
{
}

BOOST_AUTO_TEST_CASE(entity_test)
{
}

BOOST_AUTO_TEST_CASE(space_test)
{
}

BOOST_AUTO_TEST_SUITE_END()