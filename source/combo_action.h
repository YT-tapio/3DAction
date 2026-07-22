#pragma once
#include"behavior_base.h"

enum class BehaviorStatus;
class ObjectBase;
class Combo;
class CharacterBase;

class ComboAction : public BehaviorBase
{
public:

	ComboAction(std::weak_ptr<ObjectBase>owner,std::unordered_map<int,std::shared_ptr<Combo>> combos);

	~ComboAction() override;

	void Init() override;

	BehaviorStatus Update() override;
	
	void Exit() override;

	void Draw() override;
	
	void Debug() override;

	void GoNext();

	/// <summary>
	/// 現在のコンボ
	/// </summary>
	/// <returns></returns>
	const int GetCurrentcombo() const;

	/// <summary>
	/// 次のコンボへの入力を受け付けていいかのチェック
	/// </summary>
	/// <returns></returns>
	const bool CheckNextcomboReady() const;

	const bool CheckIsEnd() const;

	const bool CheckChangeCombo() const;

	const std::string GetFirstcomboAnimation() const;

private:

	/// <summary>
	/// 次のコンボに移っていいか
	/// </summary>
	/// <returns></returns>
	const bool CheckNextcombo(std::shared_ptr<CharacterBase> character) const;

	std::unordered_map<int, std::shared_ptr<Combo>> combos_;

	int current_combo_;
	bool go_next_;
	bool is_change_;

};