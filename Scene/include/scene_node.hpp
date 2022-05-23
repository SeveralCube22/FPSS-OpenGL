#pragma once

#include <set>
#include "scene_node_interface.hpp"
#include "scene_node_properties.hpp"

class SceneNode : public ISceneNode {
	friend class Scene;
protected:
	ISceneNode* parent;
	std::set<ISceneNode*> children;
	SceneNodeProperties properties;

public:
	SceneNode(unsigned int actorId, std::string name, RenderPass pass, const glm::mat4x4* to, ISceneNode* parent, const glm::mat4x4* from=nullptr) {
		parent = parent;
		properties.actorId = actorId;
		properties.name = name;
		this->setTransform(to, from);
	}

	virtual const SceneNodeProperties* const getProperties() const override { return &properties; }
	virtual void setTransform(const glm::mat4x4* to, const glm::mat4x4* from) override;
	virtual void onUpdate(Scene& scene, float delta) override;
	virtual void onRestore(const Scene& scene) override;

	virtual void preRender(Scene& scene) override;
	virtual bool isVisible(const Scene& scene) const { return false; };
	virtual void render(const Scene& scene) {} // for now do nothing for render. in the future, all scene nodes can have some sort of icons?
	virtual void renderChildren(Scene& scene) override;
	virtual void postRender(Scene& scene) override;

	virtual bool addChild(ISceneNode* node) override;
	virtual bool removeChild(unsigned int actorId) override;

	glm::vec3 getPosition() { return glm::vec3(properties.toWorld[3]); }
	void setPosition(const glm::vec3& pos) { properties.toWorld[3] = glm::vec4(pos, 1.0f); }
	glm::vec3 getDirection(const glm::vec3& pos) { return this->getPosition() - pos; }

	// methods to set the bounding box or sphere for this node

	virtual ~SceneNode();
};