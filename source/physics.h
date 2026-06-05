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
	/// 初期化
	/// </summary>
	void Init();

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

	/// <summary>
	/// 後処理
	/// </summary>
	void End();


private:

	Physics() = default;

	bool CheckHitGroundProj(std::shared_ptr<RigidBody>other,Contact& contact, const VECTOR& segment_start_pos, const float& ground_proj_length);

	bool CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other, Contact& contact, const float& ground_proj_length);

	/// <summary>
	/// 投影
	/// </summary>
	void GroundProj();

	/// <summary>
	/// 抵抗
	/// </summary>
	void Resistance();

	/// <summary>
	/// 重力
	/// </summary>
	void Gravity();

	/// <summary>
	/// 当たり判定
	/// </summary>
	void Collision();

	/// <summary>
	/// 地上なのか確認
	/// </summary>
	void CheckGround();	

	/// <summary>
	/// 自分がpairの中にいるかを確認
	/// </summary>
	/// <returns>中に自分がいるならTRUEを返す</returns>
	bool CheckCollisionedIDPair(std::pair<int,int> id_pair);

	/// <summary>
	/// 二つのペアの要素が同じかを判断する
	/// </summary>
	/// <param name="my_pair"></param>
	/// <param name="target_pair"></param>
	/// <returns></returns>
	bool IsSamePair(std::pair<int, int> my_pair, std::pair<int, int> target_pair);

private:

	const float kResistanceNum			= 0.18f;	// 抵抗の強さ
	const float kGroundProjLength		= 0.25;		// 地面のレイの許容範囲
	const float kOffsetCheckGround	= 0.015f;		// もともとのポジションから調整した値
	
	const int kLoopCollision = 10;

	int rigid_body_id_ = 0;
	Contact contact = {};

	std::list<std::pair<int, int>> collisioned_pairs_id_;

	std::unordered_map<int,std::shared_ptr<RigidBody>> id_rigid_bodies_mp_;		//各オブジェクトに付随している当たり判定とid
};