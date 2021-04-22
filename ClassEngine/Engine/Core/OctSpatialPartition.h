#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Render/3D/GameObject.h"

constexpr auto CHILDREN_NUMBER = 8;

enum class OctChildren {
	OCT_TLF,	//top left front
	OCT_BLF,	//bottom left front
	OCT_BRF,	//bottom right front
	OCT_TRF,	//top right front
	OCT_TLR,	//top left rear
	OCT_BLR,	//bottom left rear
	OCT_BRR,	//bottom right rear
	OCT_TRR		//top right rear
};

class OctNode {
public: 
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_);
	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);
	void AddCollisionObject(GameObject* obj_);
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;

private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;
};

class OctSpatialPartition {
public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);

private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};

#endif