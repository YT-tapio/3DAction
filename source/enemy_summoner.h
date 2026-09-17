#pragma once

class ISummonable;

class EnemySummoner
{
public:

	EnemySummoner();

	~EnemySummoner();

	/// <summary>
	/// ¢Š«‚³‚ê‚é‚à‚Ì‚ğ“o˜^‚·‚é
	/// </summary>
	void Registration(const std::string& name,ISummonable* summonable);

	void Summon(const std::string& name,const VECTOR& pos);

private:

	std::unordered_map<std::string, ISummonable*> summonables_;

};