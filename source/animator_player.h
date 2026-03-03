#pragma once

class AnimatorBase;
class AnimatorPlayer : public AnimatorBase
{
public:

	AnimatorPlayer(int handle);

	~AnimatorPlayer();

	void Init() override;

	void Update() override;

private:

	

};