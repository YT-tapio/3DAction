#pragma once
#include"config_name.h"

class IInput;
class Player;
class PlayerGroup;

class InputBase
{
public:

	InputBase();

	virtual ~InputBase();

	virtual void Init();

	virtual void Update();

	void Stop();

	void Start();

	void SetOwner(Player* owner);

	virtual void SetPlayerGroup(std::weak_ptr<PlayerGroup> player_group) {};

	Player* GetOwner();

	virtual const int GetPlayerChangeNum(const int& current_player_id) const;

	/// <summary>
	/// プレイヤーかどうか
	/// </summary>
	/// <returns></returns>
	virtual const bool CheckIsPlayer() const;

	virtual const bool IsPush(ConfigName name) const;

	virtual const bool IsDash() const;

	virtual const bool IsPunch() const;

	virtual const bool IsAvoid() const;

	virtual const bool IsJump() const;

	virtual const bool IsNormalSkill() const;

	virtual const bool IsStrongSkill() const;

	virtual const bool IsLockOnEnemy() const;

	virtual const bool GoNextScene() const;

	virtual const bool GoResult() const;

	virtual const bool Retry() const;

	virtual const bool GameToTitle() const;

	virtual const VECTOR GetMoveDir() const;

	virtual const VECTOR GetCameraDir() const;

	virtual const VECTOR GetCameraVelocity() const;

protected:

	// オーナーを取得する
	Player* owner_;

	bool is_stop_;
	bool is_start_;

private:



};
