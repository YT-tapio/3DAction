#pragma once
#include"behavior_base.h"

class Conbo : public BehaviorBase
{
public:

	Conbo(float min_ratio,float max_ratio,std::string my_anim_name,std::shared_ptr<BehaviorBase> behavior, std::weak_ptr<ObjectBase> owner);

	~Conbo() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

	/// <summary>
	/// 次のコンボにうつれるかをチェック
	/// </summary>
	/// <returns></returns>
	const bool CheckNextReady() const;

private:

	std::shared_ptr<BehaviorBase> behavior_;
	
	std::string my_anim_name_;
	float min_ratio_;
	float max_ratio_;

};