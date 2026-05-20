#pragma once

enum class BehaviorStatus;
class BehaviorBase;


/// <summary>
/// 予備動作のbehavior,アニメーションが終了したときにcompleteを返す。
/// </summary>
class AnimationCharge : public BehaviorBase
{
public:

	AnimationCharge(std::weak_ptr<ObjectBase> onwer, std::string my_anim_name,float timing_ratio);

	~AnimationCharge() override;

	void Init() override;

	void Entry() override;

	BehaviorStatus Update() override;

	void Exit() override;

	void Debug() override;


private:

	std::string my_anim_name_;	//自分のアニメーション
	float timing_ratio_;				//予備動作の終了ratio
};