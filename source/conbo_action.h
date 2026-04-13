#pragma once
#include"behavior_base.h"

class ObjectBase;
class Conbo;

class ConboAction : public BehaviorBase
{
public:

	ConboAction(std::weak_ptr<ObjectBase>owner,std::unordered_map<int,std::shared_ptr<Conbo>> conbos);

	~ConboAction() override;

	void Init() override;

	void Update() override;
	
	void Draw() override;
	
	void Debug() override;

	void GoNext();

	/// <summary>
	/// 次のコンボへいけるかのチェック
	/// </summary>
	/// <returns></returns>
	const bool CheckNextConboReady() const;

private:

	std::unordered_map<int, std::shared_ptr<Conbo>> conbos_;

	int current_conbo_;
	
	bool is_active_;
	bool go_next_;

};