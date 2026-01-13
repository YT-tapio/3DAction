#pragma once
#include<list>
class RigidBody;

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

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

private:

	Physics() = default;
	
	bool CheckHit(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other);

	bool CheckHitFoot(std::shared_ptr<RigidBody> me, std::shared_ptr<RigidBody> other);

	void FixPos(std::shared_ptr<RigidBody>me, std::shared_ptr<RigidBody> other);

	void Resistance();

	void CheckGround();

	const float kResistanceNum = 0.2f;	//抵抗の強さ

	std::list<std::shared_ptr<RigidBody>> rigid_bodies_;		//各オブジェクトに付随している当たり判定たち
};