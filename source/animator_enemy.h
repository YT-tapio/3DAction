#pragma once
#include"animator_base.h"

class EnemyBase;
class AnimatorEnemy : public AnimatorBase
{
public:

	AnimatorEnemy(int handle, std::shared_ptr<EnemyBase> enemy,std::string data_name);

	~AnimatorEnemy() override;

protected:

	void ChangeAnimation() override;

private:

	std::shared_ptr<const EnemyBase> enemy_;

};