#pragma once
#include"skill_base.h"

class ObjectBase;

class PunchSkill : public SkillBase
{
public:

	PunchSkill(std::weak_ptr<Player>owner,VECTOR* pos,const float r);

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
};