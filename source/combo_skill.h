#pragma once
#include"skill_base.h"

class BehaviorBase;
class ObjectBase;
class Player;
class ComboAction;

class ComboSkill : public SkillBase
{
public:

	ComboSkill(std::weak_ptr<Player> owner, std::shared_ptr<BehaviorBase> behavior, std::unordered_map<int, std::pair<float, float>> approach_speed_ratio_mp, SkillType type, float cool_time);

	~ComboSkill() override;

	void Init() override;

	void Update() override;

	void Draw() override;

	void Debug() override;

private:

	/// <summary>
	/// •â³
	/// </summary>
	void Correction(std::shared_ptr<ComboAction> combo_action);

	bool IsStartcomboAction(std::shared_ptr<ComboAction> combo_action);

	bool CheckGoNextcombo(std::shared_ptr<ComboAction> combo_action);

	// ƒRƒ“ƒ{‚ÌUŒ‚‚Ì•â³‚ğŠi”[‚µ‚Ä‚¢‚é
	// “G‚É‹ß‚Ã‚­Û‚ÌƒXƒs[ƒh
	// ‚Ç‚ê‚­‚ç‚¢‚Ì‹——£‚Å•â³‚ğ‚·‚é‚©‚ÌŠ„‡
	std::unordered_map<int, std::pair<float, float>> id_approach_speed_ratio_mp_;

};