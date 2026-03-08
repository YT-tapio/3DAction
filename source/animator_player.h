#pragma once

class AnimatorBase;
class Player;
class AnimatorPlayer : public AnimatorBase
{
public:

	AnimatorPlayer(int handle, std::shared_ptr<Player> player);

	~AnimatorPlayer() override;


	void Update() override;

private:

	const std::string kNothing	= "nothing";
	const std::string kIdle			= "idle";
	const std::string kJogging	= "jogging";
	const std::string kRun			= "run";
	const std::string kPunch		= "punch";

	std::shared_ptr<const Player> player_;
};