#pragma once

enum class AttackType;
class VariableTimer;
class Status;

class ConditionTimer;
class StatusContainer
{
public:

	StatusContainer(const std::string owner_name, const VECTOR& hp_pos, const VECTOR& hp_size);

	~StatusContainer();

	void Init();

	void Update();

	void Debug();

	/// <summary>
	/// スタミナを減らす
	/// </summary>
	/// <param name="down_value"></param>
	void StaminaDown(const float down_value);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="up_value"></param>
	void StaminaUp(const float up_value);

	/// <summary>
	/// 全回復
	/// </summary>
	void StaminaUpMax();

	/// <summary>
	/// ダメージを受ける
	/// </summary>
	/// <param name="atk"></param>
	/// <param name="type"></param>
	void TakeDamage(float atk,AttackType type);

	/// <summary>
	/// 回復
	/// </summary>
	/// <param name="heal"></param>
	void TakeHeal(float heal);

	/// <summary>
	/// もともとのステータス
	/// </summary>
	/// <returns></returns>
	const Status GetBaseStatus() const;

	/// <summary>
	/// 現在のステータス
	/// </summary>
	/// <returns></returns>
	const Status GetCurrentStatus() const;

	/// <summary>
	/// スタミナを使えるか
	/// </summary>
	/// <returns></returns>
	const bool CanUseStamina() const;

private:

	void StaminaUpdate();

	/// <summary>
	/// maxを超えたらTRUEを返す
	/// </summary>
	/// <returns></returns>
	bool StaminaRecovery();

	void LoadFile(const std::string owner_name);

private:

	// スタミナ回復を行うインターバルのタイマー：このタイマーがたまればスタミナを回復
	std::shared_ptr<ConditionTimer> stamina_recovery_timer_;
	
	// TODO：バフ系は後から


	Status base_status_;		// 初期状態
	Status current_status_;		// 現在の状態

	float stamina_recovery_value_;

	bool can_use_stamina_;

};
