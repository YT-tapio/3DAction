#pragma once

class AnimatorBase;
class AnimatorPlayer : public AnimatorBase
{
public:

	AnimatorPlayer(int handle);

	~AnimatorPlayer();


	void Update() override;

private:

	

};