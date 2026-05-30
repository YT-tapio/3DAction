#pragma once
#include"animator_base.h"

class EnemyBase;
class AnimatorEnemy : public AnimatorBase
{
public:

	AnimatorEnemy(int handle, std::string data_name);

	~AnimatorEnemy() override;

protected:

	void ChangeAnimation() override;

private:

	std::weak_ptr<const EnemyBase> enemy_;

};