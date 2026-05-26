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

	bool CheckHitGroundProj(std::shared_ptr<RigidBody>other,Contact& contact, const VECTOR& segment_start_pos, const float& ground_proj_length);

	bool CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other, Contact& contact, const float& ground_proj_length);

	void GroundProj();

	void Resistance();

	void Gravity();

	void Collision();

	void CheckGround();	

private:

	const float kResistanceNum			= 0.18f;	// 抵抗の強さ
	const float kGroundProjLength		= 0.25;		// 地面のレイの許容範囲
	const float kOffsetCheckGround	= 0.015f;		// もともとのポジションから調整した値
	
	int rigid_body_id_ = 0;
	Contact contact = {};


	std::unordered_map<int,std::shared_ptr<RigidBody>> id_rigid_bodies_mp_;		//各オブジェクトに付随している当たり判定とid
};