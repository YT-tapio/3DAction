#pragma once

struct BuffData;
enum class BuffType;
/// <summary>
/// バフ,デバフの管理を行う
/// </summary>
class StatusBuffContainer
{
public:

	StatusBuffContainer();

	~StatusBuffContainer();

	void Init();

	void Update();

private:

	// バフの量
	const int kMaxBuff = 5;

	//std::vector<Condition> buffs;

	// バフ群
	std::unordered_map<BuffType,std::vector<std::pair<bool,BuffData>>> buffs_;

	// デバフ群
	std::unordered_map<BuffType,std::vector<std::pair<bool, BuffData>>> debuffs_;
};
