#pragma once
#include<vector>

class ColliderBase;

class ColliderGroup
{
public:

	ColliderGroup(std::vector<std::shared_ptr<ColliderBase>> collider);
	
	~ColliderGroup();

	const std::vector<std::shared_ptr<ColliderBase>> GetColliders() const;

private:

	std::vector<std::shared_ptr<ColliderBase>> colliders_;

};