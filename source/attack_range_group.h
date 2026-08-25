#pragma once

class AttackRangeCircle;
class AttackRangeRectangle;

// UŒ‚”ÍˆÍ‚ğ•`‰æ‚·‚é•¨‚ğ“Š‡‚·‚é
class AttackRangeGroup
{
public:

	static AttackRangeGroup& GetInstance()
	{
		static AttackRangeGroup instance;
		return instance;
	}

	AttackRangeGroup(const AttackRangeGroup&) = delete;
	AttackRangeGroup& operator = (const AttackRangeGroup&) = delete;

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
	int CircleDrawRequest(const VECTOR& pos, const VECTOR& scale, std::function<bool()>end_function);

	int RectangleDrawRequest(const VECTOR& pos, const VECTOR& scale, const VECTOR& dir,std::function<bool()> end_function);

	void CircleSetPos(const int& id,const VECTOR& pos);

	void RectangleSetPos(const int& id, const VECTOR& pos);

	void RectangleSetDir(const int& id, const VECTOR& dir);

private:

	AttackRangeGroup();

private:

	static const int kMaxAttackRangeNum = 5;

	std::vector<std::pair<bool,std::shared_ptr<AttackRangeCircle>>> attack_ranges_ui_;
	std::unordered_map<int,std::function<bool()>> end_functions_;

	std::vector<std::pair<bool, std::shared_ptr<AttackRangeRectangle>>> attack_range_rectangles_ui_;
	std::unordered_map<int, std::function<bool()>> rectangle_end_functions_;

};