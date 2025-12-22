#pragma once

class ColliderBase;
class ObjectBase;

class RigidBody
{
public:

	RigidBody(std::shared_ptr<ColliderBase> coll,VECTOR* pos);

	~RigidBody();

	void Init(void (*op)(std::shared_ptr<ObjectBase>), std::weak_ptr<ObjectBase> object);

	void Update(const VECTOR& vel,const VECTOR& dir);

	void (*hit)(std::shared_ptr<ObjectBase>);

private:

	VECTOR* pos_;
	VECTOR vel_;
	VECTOR dir_;

	std::shared_ptr<ColliderBase>	coll_;		// Ž©•ª‚Ì“–‚½‚è”»’è
	std::weak_ptr<ObjectBase>		object_;	// Ž©•ª‚Ì‚±‚Æ‚ð’m‚Á‚Ä‚¢‚éobje‚Ì“o˜^

};