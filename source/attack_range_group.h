#pragma once

class AttackRange;

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
	int DrawRequest(const VECTOR& pos, const VECTOR& scale, std::function<bool()>end_function);

private:

	AttackRangeGroup();

private:

	static const int kMaxAttackRangeNum = 5;

	std::vector<std::pair<bool,std::shared_ptr<AttackRange>>> attack_ranges_ui_;
	std::unordered_map<int,std::function<bool()>> end_functions_;
};