#pragma once
#include"behavior_base.h"

class ObjectBase;
class Conbo;
class CharacterBase;

class ConboAction : public BehaviorBase
{
public:

	ConboAction(std::weak_ptr<ObjectBase>owner,std::unordered_map<int,std::shared_ptr<Conbo>> conbos);

	~ConboAction() override;

	void Init() override;

	void Update() override;
	
	void Exit() override;

	void Draw() override;
	
	void Debug() override;

	void GoNext();

	/// <summary>
	/// 現在のコンボ
	/// </summary>
	/// <returns></returns>
	const int GetCurrentConbo() const;

	/// <summary>
	/// 次のコンボへの入力を受け付けていいかのチェック
	/// </summary>
	/// <returns></returns>
	const bool CheckNextConboReady() const;

	const bool CheckIsEnd() const;

	const bool CheckChangeConbo() const;

	const std::string GetFirstConboAnimation() const;

private:

	/// <summary>
	/// 次のコンボに移っていいか
	/// </summary>
	/// <returns></returns>
	const bool CheckNextConbo(std::shared_ptr<CharacterBase> character) const;

	std::unordered_map<int, std::shared_ptr<Conbo>> conbos_;

	int current_conbo_;
	bool go_next_;
	bool is_change_;

};