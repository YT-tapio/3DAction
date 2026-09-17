#include<unordered_map>
#include<string>
#include"DxLib.h"
#include"enemy_summoner.h"
#include"summonable_interface.h"

EnemySummoner::EnemySummoner()
{

}

EnemySummoner::~EnemySummoner()
{

}

void EnemySummoner::Registration(const std::string& name,ISummonable* summonable)
{
	summonables_[name] = summonable;
}

void EnemySummoner::Summon(const std::string& name,const VECTOR& pos)
{
	auto summonable = summonables_.find(name);
	if (summonable == summonables_.end()) 
	{
		printfDx("—v‘f‚ª‘¶Ý‚µ‚Ü‚¹‚ñ\n");
		return;
	}
	summonable->second->Summon(pos);
}
