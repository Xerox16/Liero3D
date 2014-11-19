#include "parts.h"

#include <irrlicht.h>

#include "entity.h"
#include "state.h"
#include "action.h"
#include "utilities.h"

using namespace irr;
using namespace scene;
using namespace core;

template <typename T> class SceneNode : public State {
public:
	SceneNode(T* node) : State(), sceneNode_(node) {
	}
	
	//implement copy constructor for correct cloning of scene node
	SceneNode(const SceneNode<T>& rhs) : State() {
		sceneNode_ = static_cast<T>(rhs.sceneNode_->clone());
	}
	
	T* getSceneNode() const {
		return sceneNode_;
	}
	
	SceneNode<T>* clone() const {
		return new SceneNode<T>(*this);
	}
	
private:
	T* sceneNode_;
};

core::vector3df getVectorFromJsonArray(const boost::property_tree::ptree& tree) {
	//if position array has correct size, fetch the three elements via incrementing iterator to first element two times
	if(tree.size() == 3) {
		auto begin = tree.begin();
		float x = (begin++)->second.get_value<float>();
		float y = (begin++)->second.get_value<float>();
		float z = begin->second.get_value<float>();
		return core::vector3df(x,y,z);
	} else {
		return core::vector3df();
	}
}

void nodeQuery(irr::scene::ISceneNode* node, const boost::property_tree::ptree& tree) {
	boost::property_tree::ptree branch;
	
	//check if position is given
	branch = tree.get_child("position");
	node->setPosition(getVectorFromJsonArray(branch));
}


void register_scene_node(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	irr::scene::ISceneNode* sceneNode = context.irrH_->smgr->addEmptySceneNode();
	
	entity.addState(std::shared_ptr<SceneNode<ISceneNode> >(new SceneNode<ISceneNode>(sceneNode)));
	entity.addType<SceneNode<ISceneNode> >("scene_node");
}

void register_cube_scene_node(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	irr::scene::IMeshSceneNode* meshSceneNode = context.irrH_->smgr->addCubeSceneNode();

	entity.addState(std::shared_ptr<SceneNode<IMeshSceneNode> >(new SceneNode<IMeshSceneNode>(meshSceneNode)));
	entity.addType<SceneNode<IMeshSceneNode> >("cube_scene_node");
}

void register_light_scene_node(const boost::property_tree::ptree& tree, Entity& entity, EntityCreationContext& context)
{
	irr::scene::ILightSceneNode* lightSceneNode = context.irrH_->smgr->addLightSceneNode();
	
	entity.addState(std::shared_ptr<SceneNode<ILightSceneNode> >(new SceneNode<ILightSceneNode>(lightSceneNode)));
	entity.addType<SceneNode<ILightSceneNode> >("light_scene_node");
}



void registerParts(EntityComposer& entityComposer)
{
	entityComposer.registerComposer("scene_node",register_scene_node);
	entityComposer.registerComposer("cube_scene_node",register_cube_scene_node);
	entityComposer.registerComposer("light_scene_node",register_light_scene_node);
}
