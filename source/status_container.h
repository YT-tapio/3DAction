#pragma once

enum class AttackType;
class VariableTimer;
class Status;
class ActiveStatModifireGroup;

class ConditionTimer;
class IPlayerUIGroup;
class StatusContainer
{
public:

	StatusContainer(const std::string owner_name, const VECTOR& hp_pos, const VECTOR& hp_size);

	~StatusContainer();

	void Init();

	void Update();

	void Debug();

	/// <summary>
	/// スタミナの回復を止める
	/// </summary>
	void StopHealStamina();

	/// <summary>
	/// スタミナの回復を再開する
	/// </summary>
	void StartHealStamina();

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
	float TakeDamage(float atk,AttackType type);

	/// <summary>
	/// 数値の回復
	/// </summary>
	/// <param name="heal"></param>
	void TakeHeal(float heal);

	/// <summary>
	/// 引数の効果を適応させる
	/// </summary>
	/// <param name="name">効果名</param>
	void Activation(const std::string& name, std::shared_ptr<IPlayerUIGroup> player_ui_group);

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
	/// 正規分布した物理ダメージ
	/// </summary>
	/// <returns></returns>
	const float GetPhysicalATK() const;

	/// <summary>
	/// 正規分布した魔法ダメージ
	/// </summary>
	/// <returns></returns>
	const float GetMagicATK() const;

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

	/// <summary>
	/// 
	/// </summary>
	/// <param name="owner_name"></param>
	void LoadFile(const std::string owner_name);

private:

	// スタミナ回復を行うインターバルのタイマー：このタイマーがたまればスタミナを回復
	std::shared_ptr<ConditionTimer> stamina_recovery_timer_;
	
	// ステータスにバフやデバフをかける
	std::shared_ptr<ActiveStatModifireGroup> stat_modifire_group_;

	Status base_status_;		// 初期状態
	Status current_status_;		// 現在の状態

	float stamina_recovery_value_;

	bool can_use_stamina_;
	bool can_heal_stamina_;
};
