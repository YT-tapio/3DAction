#pragma once

#include"condition_timer.h"

class EnemyCoolTimeController
{
public:

	EnemyCoolTimeController();

	~EnemyCoolTimeController();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="time"></param>
	void AddCoolTime(const std::string& name, const float& time);

	/// <summary>
	/// 初期化・クールタイムのリセット
	/// </summary>
	void Init();

	/// <summary>
	/// クールタイムの更新
	/// </summary>
	void Update();

	/// <summary>
	/// スタート
	/// </summary>
	/// <param name="name"></param>
	void Start(const std::string& name);

	/// <summary>
	/// クールタイムが終了しているか
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	const bool GetIsEnd(const std::string& name) const;

private:

	// クールタイムの名前
	std::unordered_map<std::string, std::shared_ptr<ConditionTimer>> cool_times_;

};