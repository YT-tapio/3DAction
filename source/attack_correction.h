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

	/// <summary>
	/// “G‚ª’†‚É‚¢‚é‚©‚Æ‚Ì”»’f‚ÆA“G‚É‹ß‚Ã‚­‚½‚ß‚ÌƒxƒNƒgƒ‹‚ğo‚·ŠÖ”
	/// </summary>
	/// <param name="objects">‚Ü‚í‚è‚Ìobject</param>
	/// <param name="player"></param>
	/// <param name="velocity"></param>
	/// <param name="speed"></param>
	/// <param name="move_ratio"></param>
	/// <param name="detection_dist"></param>
	/// <returns></returns>
	bool ApproachTheNearestEnemy(std::shared_ptr<Player> player,
		VECTOR& velocity, float speed,float move_ratio);
	
private:

	AttackCorrection();

};