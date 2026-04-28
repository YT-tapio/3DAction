#pragma once
#include"behavior_base.h"
enum class BehaviorStatus;

class Conbo : public BehaviorBase
{
public:

	Conbo(std::weak_ptr<ObjectBase> owner,float min_ratio,float max_ratio,float go_next_timing,std::string my_anim_name,std::shared_ptr<BehaviorBase> behavior);

	~Conbo() override;

	void Init() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Draw() override;

	void Debug() override;

	/// <summary>
	/// 次のコンボにうつれる入力の猶予
	/// </summary>
	/// <returns></returns>
	const bool CheckNextReady() const;

	/// <summary>
	/// 次のコンボ(animation)に移れるかのチェック
	/// </summary>
	/// <returns></returns>
	const bool CheckAnimation() const;

	const bool CheckIsEnd() const;

	const std::string GetMyAnimName() const;

private:

	std::shared_ptr<BehaviorBase> behavior_;
	
	std::string my_anim_name_;
	float min_ratio_;
	float max_ratio_;
	float go_next_timing_;

};