#include "defines.h"

#include <boost/log/trivial.hpp>
#include <boost/exception/all.hpp>

#include "state.h"
#include "entity.h"
#include "action.h"
#include "space.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(entity_system_test)

class Int : public State {
public:
	Int* clone() const {
		return new Int(*this);
	}
	
	int i = 0;
};

class Double : public State {
public:
	Double* clone() const {
		return new Double(*this);
	}
	
	double d = 0.0;
};

class AddToInt : public Action {
public:
	AddToInt* clone() const {
		return new AddToInt(*this);
	}
	
protected:
	void apply(Entity* target) {
		auto int_ = target->getState<Int>();
		int_->i++;
	}
};

class AddToDouble : public Action {
public:
	AddToDouble* clone() const {
		return new AddToDouble(*this);
	}
	
protected:
	void apply(Entity* target) {
		auto double_ = target->getState<Double>();
		double_->d++;
	}
};

BOOST_AUTO_TEST_CASE(state_test)
{
	Int oldInt;
	oldInt.i = 2;
	std::shared_ptr<Int> newInt(oldInt.clone());
	
	BOOST_REQUIRE_EQUAL(oldInt.i, newInt->i);
}

BOOST_AUTO_TEST_CASE(entity_test)
{
	Entity entity;
	
	//check key management
	long key = 29182991;
	entity.setKey(key);
	BOOST_REQUIRE_EQUAL(key, entity.getKey());
	
	//create states
	std::shared_ptr<Int> oldInt(new Int);
	std::shared_ptr<Int> newInt;
	Int* newIntPtr;
	
	std::shared_ptr<Double> oldDouble(new Double);
	std::shared_ptr<Double> newDouble;
	Double* newDoublePtr;
	
	//add states to entity
	entity.addState(oldInt);
	entity.addState(oldDouble);
	
	//fetch states from entity
	newInt = entity.getStatePtr<Int>();
	newIntPtr = entity.getState<Int>();
	newDouble = entity.getStatePtr<Double>();
	newDoublePtr = entity.getState<Double>();
	
	//compare the original to the fetched states
	BOOST_REQUIRE_EQUAL(oldInt.get(), newInt.get());
	BOOST_REQUIRE_EQUAL(oldInt.get(), newIntPtr);
	BOOST_REQUIRE_EQUAL(oldDouble.get(), newDouble.get());
	BOOST_REQUIRE_EQUAL(oldDouble.get(), newDoublePtr);
	
	//remove states
	entity.removeState<Int>();
	entity.removeState<Double>();
	
	//fetch them once again
	newInt = entity.getStatePtr<Int>();
	newIntPtr = entity.getState<Int>();
	newDouble = entity.getStatePtr<Double>();
	newDoublePtr = entity.getState<Double>();
	
	//now they should be NULL pointers
	BOOST_REQUIRE(newInt.get()== NULL);
	BOOST_REQUIRE(newIntPtr == NULL);
	BOOST_REQUIRE(newDouble.get() == NULL);
	BOOST_REQUIRE(newDoublePtr == NULL);
	
	//create actions
	std::shared_ptr<AddToInt> oldAddInt(new AddToInt);
	std::shared_ptr<AddToInt> newAddInt;
	AddToInt* newAddIntPtr;
	
	std::shared_ptr<AddToDouble> oldAddDouble(new AddToDouble);
	std::shared_ptr<AddToDouble> newAddDouble;
	AddToDouble* newAddDoublePtr;
	
	//add them to the entity
	entity.addAction(oldAddInt);
	entity.addAction(oldAddDouble);
	
	//fetch them from entity
	newAddInt = entity.getActionPtr<AddToInt>();
	newAddIntPtr = entity.getAction<AddToInt>();
	newAddDouble = entity.getActionPtr<AddToDouble>();
	newAddDoublePtr = entity.getAction<AddToDouble>();
	
	//compare the original to the fetched actions
	BOOST_REQUIRE_EQUAL(oldAddInt.get(), newAddInt.get());
	BOOST_REQUIRE_EQUAL(oldAddInt.get(), newAddIntPtr);
	BOOST_REQUIRE_EQUAL(oldAddDouble.get(), newAddDouble.get());
	BOOST_REQUIRE_EQUAL(oldAddDouble.get(), newAddDoublePtr);
	
	//delete actions from entity
	entity.removeAction<AddToInt>();
	entity.removeAction<AddToDouble>();
	
	//fetch them once again
	newAddInt = entity.getActionPtr<AddToInt>();
	newAddIntPtr = entity.getAction<AddToInt>();
	newAddDouble = entity.getActionPtr<AddToDouble>();
	newAddDoublePtr = entity.getAction<AddToDouble>();
	
	
	//now they should be NULL pointers
	BOOST_REQUIRE(newAddInt.get()== NULL);
	BOOST_REQUIRE(newAddIntPtr == NULL);
	BOOST_REQUIRE(newAddDouble.get() == NULL);
	BOOST_REQUIRE(newAddDoublePtr == NULL);
	
	//check clone function
	
	//therefore add states and actions
	entity.addState(oldInt);
	entity.addState(oldDouble);
	entity.addAction(oldAddInt);
	entity.addAction(oldAddDouble);
	
	//define cloned entity
	std::shared_ptr<Entity> clone(entity.clone());
	
	BOOST_REQUIRE(entity.getKey() 					== clone->getKey());
	BOOST_REQUIRE(entity.getSpace() 				== clone->getSpace());
	BOOST_REQUIRE(entity.getState<Int>() 			!= clone->getState<Int>());
	BOOST_REQUIRE(entity.getState<Double>() 		!= clone->getState<Double>());
	BOOST_REQUIRE(entity.getState<Int>()->i 			== clone->getState<Int>()->i);
	BOOST_REQUIRE(entity.getState<Double>()->d 		== clone->getState<Double>()->d);
	BOOST_REQUIRE(entity.getAction<AddToInt>()		!= clone->getAction<AddToInt>());
	BOOST_REQUIRE(entity.getAction<AddToDouble>() != clone->getAction<AddToDouble>());
}

BOOST_AUTO_TEST_CASE(action_test)
{
}

BOOST_AUTO_TEST_CASE(space_test)
{
}

BOOST_AUTO_TEST_SUITE_END()