#pragma once
#include"popup_ui_group_interface.h"

class DamageUI;
class NumberPopupUI;

class PopupUIGroup : public IPopupUIGroup
{
public:

	PopupUIGroup();
	
	~PopupUIGroup();

	void Awake();

	void Init();

	void Update();

	const void Draw() const;

	/// <summary>
	/// プレイヤーのダメージを出現
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="damage"></param>
	/// <param name="is_critical"></param>
	void SpawnPlayerDamageUI(const VECTOR& pos,const float& damage, const bool is_critical) override;

	/// <summary>
	/// プレイヤーの回復量を出現
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="heal"></param>
	void SpawnPlayerHealUI(const VECTOR& pos, const float& heal) override;

	/// <summary>
	/// 敵のダメージ量を出現
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="damage"></param>
	/// <param name="is_critical"></param>
	void SpawnEnemyDamageUI(const VECTOR& pos, const float& damage, const bool is_critical) override;

	/// <summary>
	/// 敵の回復量を出現
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="heal"></param>
	void SpawnEnemyHealUI(const VECTOR& pos, const float& heal) override;

private:

	/// <summary>
	/// 引数で受け取った物をupdateする
	/// </summary>
	/// <param name="popup_uis"></param>
	void UpdateUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis);

	/// <summary>
	/// 引数で受け取った物を描画する
	/// </summary>
	/// <param name="popup_uis"></param>
	/// <returns></returns>
	const void DrawUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis) const;

	/// <summary>
	/// 引数で受け取った物を出現
	/// </summary>
	/// <param name="uis"></param>
	void SpawnUI(std::vector<std::shared_ptr<NumberPopupUI>> popup_uis, const VECTOR& pos, const float& damage, const bool is_critical = FALSE);

private:

	const int kMaxDamageUI = 10;
	const int kMaxHealUI = 5;

	std::vector<std::shared_ptr<NumberPopupUI>> player_damage_uis_;	// playerがダメージを受けた際に描画する
	std::vector<std::shared_ptr<NumberPopupUI>> player_heal_uis_;	// playerが回復量を受けた際に描画する
	std::vector<std::shared_ptr<NumberPopupUI>> enemy_damage_uis_;	// enemyが攻撃を受けた際に描画する
	std::vector<std::shared_ptr<NumberPopupUI>> enemy_heal_uis_;	// enemyが回復量を受けた際に描画する


};