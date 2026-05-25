#pragma once
#include<list>
#include"contact.h"
class RigidBody;

class ColliderBase;
class Sphere;
class Capsule;
struct Contact;

class Physics
{
public:

	static Physics& GetInstance()
	{
		static Physics instance;
		return instance;
	}

	Physics(const Physics&) = delete;
	Physics& operator = (const Physics&) = delete;

	/// <summary>
	/// rigid_bodyの登録
	/// </summary>
	/// <param name="body"></param>
	void AddBody(std::shared_ptr<RigidBody> body);

	//
	void Debug();

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();


private:

	Physics() = default;
	
	bool CheckHit(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other);

	bool CheckHitGroundProj(std::shared_ptr<RigidBody>other,Contact& contact, const VECTOR& segment_start_pos, const float& ground_proj_length);

	bool CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other, Contact& contact, const float& ground_proj_length);

	void GroundProj();

	void FixPos(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other);

	void SphereFixPos(std::shared_ptr<Sphere> me, std::shared_ptr<ColliderBase> other);

	void CapsuleFixPos(std::shared_ptr<Capsule> me, std::shared_ptr<ColliderBase> other);

	void Resistance();

	void Gravity();

	void Collision();

	void CheckGround();	

private:

	//0.18
	const float kResistanceNum			= 0.18f;	// 抵抗の強さ
	const float kGroundProjLength		= 0.25;		// 地面のレイの許容範囲
	const float kOffsetCheckGround	= 0.015f;	//もともとのポジションから調整した値
	Contact contact = {};

	std::list<std::shared_ptr<RigidBody>> rigid_bodies_;		//各オブジェクトに付随している当たり判定たち
};