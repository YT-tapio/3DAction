#pragma once

class ObjectBase;
class Player;

// UŒ‚‚Ì•â³
class AttackCorrection
{
public:

	static AttackCorrection& GetInstance()
	{
		static AttackCorrection instance;
		return instance;
	}

	AttackCorrection(const AttackCorrection&) = delete;
	AttackCorrection& operator = (const AttackCorrection&) = delete;

	// “G‚ª’†‚É‚¢‚é‚©‚ğ”»’f‚·‚é
	bool ApproachTheEnemy(std::vector<std::shared_ptr<ObjectBase>> objects,
		std::shared_ptr<Player> player,VECTOR& velocity, float speed,float move_ratio,float detection_dist);
	
private:

	AttackCorrection();

};