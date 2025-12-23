#pragma once

class ObjectBase;
class ColliderBase;
class IHit;

class RigidBody
{
public:

	RigidBody(std::shared_ptr<ColliderBase> coll,VECTOR* pos);

	~RigidBody();

	void Init(std::weak_ptr<IHit> object);

	void Update(const VECTOR& vel,const VECTOR& dir);

	void OnHit(std::shared_ptr<IHit> object);

	std::shared_ptr<ColliderBase> GetCollider();

	std::shared_ptr<IHit> GetIHitObject();

private:

	VECTOR* pos_;
	VECTOR vel_;
	VECTOR dir_;

	std::shared_ptr<ColliderBase>	coll_;		// 自分の当たり判定
	std::weak_ptr<IHit>				object_;	// インターフェースを継承したオブジェクト

};