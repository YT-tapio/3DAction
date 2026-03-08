#pragma once
#include"animator_base.h"

class AnimatorEnemy : public AnimatorBase
{
public:

	AnimatorEnemy(const char* data_file_path, int handle);

	~AnimatorEnemy() override;

	void Update()override;


private:



};