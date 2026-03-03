#pragma once

class AnimatorBase;
class Player;
class AnimatorPlayer : public AnimatorBase
{
public:

	AnimatorPlayer(int handle, std::shared_ptr<Player> player);

	~AnimatorPlayer();


	void Update() override;

private:

	std::shared_ptr<const Player> player_;

};