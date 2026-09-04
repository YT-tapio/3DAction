#pragma once
#include"attack_range_group_interface.h"

class AttackRangeCircle;
class AttackRangeRectangle;

// UŒ‚”ÍˆÍ‚ğ•`‰æ‚·‚é•¨‚ğ“Š‡‚·‚é
class AttackRangeGroup : public IAttackRangeGroup
{
public:

	AttackRangeGroup();
	
	~AttackRangeGroup() override;

	void Awake();

	void Init();

	void Update();

	void Draw();

	void End();

	/// <summary>
	/// •`‰æ‚ª‚Å‚«‚È‚¢—Ê‚È‚ç-1‚ğ•Ô‚·
	/// </summary>
	/// <param name="scale"></param>
	/// <returns>-1ˆÈŠO‚Í¬Œ÷</returns>
	int CircleDrawRequest(const VECTOR& pos, const VECTOR& scale,const float& time, std::function<bool()>end_function) override;

	int RectangleDrawRequest(const VECTOR& pos, const VECTOR& scale, const VECTOR& dir, const float& time, std::function<bool()> end_function) override;

	void CircleSetPos(const int& id,const VECTOR& pos) override;

	void RectangleSetPos(const int& id, const VECTOR& pos) override;

	void RectangleSetDir(const int& id, const VECTOR& dir) override;

private:

private:

	const int kMaxAttackRangeNum = 5;

	std::vector<std::pair<bool,std::shared_ptr<AttackRangeCircle>>> attack_ranges_ui_;
	std::unordered_map<int,std::function<bool()>> end_functions_;

	std::vector<std::pair<bool, std::shared_ptr<AttackRangeRectangle>>> attack_range_rectangles_ui_;
	std::unordered_map<int, std::function<bool()>> rectangle_end_functions_;

};