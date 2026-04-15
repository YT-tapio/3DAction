#pragma once
#include"correction_skill.h"

class CloseCorrectionSkill : public CorrectionSkill
{
public:

	CloseCorrectionSkill(std::weak_ptr<Player> owner,std::shared_ptr<BehaviorBase> behaivor,const float detection_radius);

	virtual ~CloseCorrectionSkill() override;

	virtual void Init() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void Debug() override;

protected:

	//補正をかける
	void Correction() override;

	//検出範囲
	float detection_radius_;

private:



};