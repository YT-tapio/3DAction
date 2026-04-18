#pragma once
#include"skill_base.h"

class ObjectBase;

class PunchSkill : public SkillBase
{
public:

	PunchSkill(std::weak_ptr<Player> owner,VECTOR* pos,std::string my_anim_name,const float r, float min_coll_ratio, 
		float max_coll_ratio,const float detection_radius,float approach_speed, float approach_ratio);

	~PunchSkill() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

protected:

	void DecideTarget(std::vector<std::weak_ptr<ObjectBase>> owner_area_objects, std::shared_ptr<Player> owner);

private:

	bool CheckIsPunch(std::shared_ptr<Player> owner);

	VECTOR target_dir_;		// ターゲットの方向
	VECTOR target_pos_;		// ターゲットの位置

	std::string my_anim_name_;

	float detection_radius_;
	float approach_speed_;	// 敵に近づく際のスピード
	float approach_ratio_;			// どれくらいの距離で補正をするかの割合
};